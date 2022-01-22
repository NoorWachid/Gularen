#include "Lexer.hpp"
#include "IO.hpp"

namespace Gularen
{
	Lexer::Lexer()
	{
		Reset();
	}

	void Lexer::SetBuffer(const std::string& buffer)
	{
		this->mBuffer = buffer;
		mBufferSize = buffer.size();

		Reset();
	}

	void Lexer::SetTokens(const std::vector<Token>& tokens)
	{
		Reset();
		mBuffer.clear();

		this->mTokens = tokens;
	}

	void Lexer::Parse()
	{
		Reset();
		Add(Token(TokenType::DocumentBegin));
		ParseNewline();

		while (IsValid())
		{
			// Main switchboard
			switch (GetCurrentByte())
			{
				case '*':
					Add(Token(TokenType::Asterisk));
					Skip();
					break;

				case '_':
					Add(Token(TokenType::Underline));
					Skip();
					break;

				case '`':
					Skip();
					if (GetCurrentByte() == '`')
					{
						Skip();
						Add(Token(TokenType::Teeth));
						std::string buffer;
						while (IsValid())
						{
							if (GetCurrentByte() == '`' && GetNextByte() == '`')
							{
								Add(Token(TokenType::Text, buffer));
								Add(Token(TokenType::Teeth));
								Skip(2);
								break;
							}
							buffer += GetCurrentByte();
							Skip();
						}
					}
					else
						Add(Token(TokenType::Backtick));
					break;

				case '\r':
					Skip();
					break;

				case '\n':
				{
					size_t size = 0;
					while (IsValid() && GetCurrentByte() == '\n')
					{
						++size;
						Skip();
					}

					if (!mTokens.empty() && mTokens.back().type == TokenType::Newline)
						mTokens.back().size += size;
					else
					{
						Token token(TokenType::Newline);
						token.size = size;
						Add(std::move(token));
					}

					ParseNewline();
					break;
				}

				case '~':
					while (IsValid() && GetCurrentByte() != '\n')
						Skip();
					break;

				case '>':
					if (mInHeaderLine)
					{
						Skip();
						SkipSpaces();
						if (GetCurrentByte() == '\'')
						{
							Skip();
							std::string symbol;
							while (IsValid() && IsValidSymbol())
							{
								symbol += GetCurrentByte();
								Skip();
							}
							if (GetCurrentByte() == '\'')
							{
								Add(Token(TokenType::Anchor, symbol));
								Skip();
							}
						}
					}
					Skip();
					break;

				case '<':
					Add(Token(TokenType::RevTail, 1));
					Skip();
					break;

				case '{':
					Add(Token(TokenType::LCurlyBracket));
					Skip();
					ParseInlineFunction();
					break;

				case '}':
					Add(Token(TokenType::RCurlyBracket));
					Skip();
					break;

				case '\\':
					ParseInlineEscapedByte();
					break;

				case '|':
					Skip();
					if (!mTokens.empty() && mTokens.back().type == TokenType::Text)
					{
						// remove blankspaces of previous token
						for (size_t i = mTokens.back().value.size() - 1; i >= 0; --i)
						{
							if (mTokens.back().value[i] != ' ')
							{
								mTokens.back().value = mTokens.back().value.substr(0, i + 1);
								break;
							}
						}
					}
					Add(Token(TokenType::Pipe));
					SkipSpaces();
					break;

				case '#':
				{
					Skip();
					std::string symbol;
					while (IsValid() && IsValidSymbol())
					{
						symbol += GetCurrentByte();
						Skip();
					}
					Token token;
					token.type = TokenType::HashSymbol;
					token.value = symbol;
					Add(std::move(token));
					break;
				}
				case '@':
				{
					Skip();
					std::string symbol;
					while (IsValid() && IsValidSymbol())
					{
						symbol += GetCurrentByte();
						Skip();
					}
					Token token;
					token.type = TokenType::AtSymbol;
					token.value = symbol;
					Add(std::move(token));
					break;
				}

				default:
					if (IsValidText())
						ParseText();
					else
					{
						if (!mTokens.empty() && mTokens.back().type == TokenType::Text)
							mTokens.back().value += GetCurrentByte();
						else
							Add(Token(TokenType::Text, std::string(1, GetCurrentByte())));
						Skip();
					}
					break;
			}
		}

		Add(Token(TokenType::DocumentEnd));
	}

	std::string Lexer::GetBuffer()
	{
		return mBuffer;
	}

	Token& Lexer::GetToken(size_t index)
	{
		return mTokens[index];
	}

	void Lexer::Reset()
	{
		mInHeaderLine = false;
		mInLink = false;
		mInCodeBlock = false;

		mBufferIndex = 0;
		mTokens.clear();

		mCurrentDepth = 0;
	}

	std::vector<Token>& Lexer::GetTokens()
	{
		return mTokens;
	}

	std::string Lexer::GetTokensAsString()
	{
		std::string buffer;

		for (Token& token: mTokens)
			buffer += token.ToString() + "\n";

		return buffer + "\n";
	}

	void Lexer::ParseText()
	{
		std::string buffer;

		while (IsValid() && IsValidText())
		{
			buffer += GetCurrentByte();
			Skip();
		}

		if (!mTokens.empty() && mTokens.back().type == TokenType::Text)
			mTokens.back().value += buffer;
		else
			Add(Token(TokenType::Text, buffer));
	}

	void Lexer::ParseQuotedText()
	{
		Token token;
		token.type = TokenType::QuotedText;

		Skip();
		while (IsValid() && GetCurrentByte() != '\'')
		{
			token.value += GetCurrentByte();
			Skip();
		}
		Skip();
		Add(std::move(token));
	}

	void Lexer::ParseInlineEscapedByte()
	{
		Skip();

		switch (GetCurrentByte())
		{
			case '~': // Oneline comments
			case '\\':
			case '*':
			case '_':
			case '`':
			case '{':
			case '}':
			case '<':
				Add(Token(TokenType::Text, std::string(1, GetCurrentByte())));
				Skip();
				break;

			default:
			{
				std::string buffer(1, '\\');
				buffer += GetCurrentByte();
				Add(Token(TokenType::Text, buffer));
				Skip();
				break;
			}
		}
	}

	void Lexer::ParseNewline()
	{
		// State variables
		mInHeaderLine = false;

		if (GetCurrentByte() == ' ')
		{
			Token token(TokenType::Space);
			token.size = 1;
			Skip();

			while (IsValid() && GetCurrentByte() == ' ')
			{
				++token.size;
				Skip();
			}

			mCurrentDepth = token.size;
			Add(std::move(token));
		}
		else
			mCurrentDepth = 0;

		switch (GetCurrentByte())
		{
			case '-':
			{
				size_t size = 0;

				while (IsValid() && GetCurrentByte() == '-')
				{
					Skip();
					++size;
				}

				if (size == 1)
				{
					if (GetCurrentByte() == '>' && GetNextByte() == ' ')
					{
						Add(Token(TokenType::Arrow, 1));
						Skip();
						SkipSpaces();
					}
					else
					{
						Add(Token(TokenType::Bullet));
						SkipSpaces();
					}
				}
				else if (size == 2 && GetCurrentByte() == '>' && GetNextByte() == ' ')
				{
					Add(Token(TokenType::Arrow, 2));
					Skip();
					SkipSpaces();
				}
				else
				{
					Add(Token(TokenType::Line, size));
					SkipSpaces();

					if (mInCodeBlock)
					{
						std::string buffer;

						while (IsValid())
						{
							if (GetCurrentByte() == '\n')
							{
								Skip();
								// Skip identations or blank lines
								size_t shouldSkipCounter = 0;
								while (IsValid() && shouldSkipCounter < mCurrentDepth && GetCurrentByte() != '\n')
								{
									Skip();
									++shouldSkipCounter;
								}

								if (GetCurrentByte() == '-')
								{
									size_t laterSize = 0;

									while (IsValid() && GetCurrentByte() == '-')
									{
										++laterSize;
										Skip();
									}

									if (laterSize == size)
									{
										Add(Token(TokenType::RawText, buffer));
										Add(Token(TokenType::Line, size));
										mInCodeBlock = false;
										break;
									}
									else
									{
										if (!buffer.empty())
											buffer += "\n";
										buffer += std::string(laterSize, '-');
									}
								}
								else if (!buffer.empty())
									buffer += "\n";
							}
							else
							{
								buffer += GetCurrentByte();
								Skip();
							}
						}
					}
				}
				break;
			}

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			{
				std::string buffer;

				while (IsValid() && IsValidNumeric())
				{
					buffer += GetCurrentByte();
					Skip();
				}

				if (GetCurrentByte() == '.' && GetNextByte() == ' ')
				{
					Add(Token(TokenType::NBullet));
					Skip(2);
				}
				else
				{
					if (!mTokens.empty() && mTokens.back().type == TokenType::Text)
						mTokens.back().value += buffer;
					else
						Add(Token(TokenType::Text, buffer));
				}

				break;
			}

			case '.':
				if (GetNextByte(1) == '.' && GetNextByte(2) == ' ')
				{
					Add(Token(TokenType::NBullet));
					Skip(3);
				}
				break;

			case '[':
				if (GetNextByte(2) == ']')
				{
					Token token(TokenType::CheckBox);

					switch (GetNextByte(1))
					{
						case ' ':
							token.size = 1;
							Add(std::move(token));
							Skip(3);
							SkipSpaces();
							break;

						case '-':
							token.size = 2;
							Add(std::move(token));
							Skip(3);
							SkipSpaces();
							break;

						case '+':
							token.size = 3;
							Add(std::move(token));
							Skip(3);
							SkipSpaces();
							break;

						default:
							break;
					}
				}
				break;

			case '>':
			{
				mInHeaderLine = true;

				Skip();
				if (GetCurrentByte() == ' ')
				{
					Add(Token(TokenType::Tail, 1));
					SkipSpaces();
					break;
				}
				else if (GetCurrentByte() == '>')
				{
					Skip();
					if (GetCurrentByte() == ' ')
					{
						Add(Token(TokenType::Tail, 2));
						SkipSpaces();
					}
					else if (GetCurrentByte() == '>' && GetNextByte() == ' ')
					{
						Add(Token(TokenType::Tail, 3));
						Skip();
						SkipSpaces();
					}
					else if (GetCurrentByte() == '-' && GetNextByte(1) == '>' && GetNextByte(2) == ' ')
					{
						Add(Token(TokenType::Arrow, 3));
						Skip(2);
						SkipSpaces();
					}
					else if (GetCurrentByte() == '-' && GetNextByte(1) == '-' && GetNextByte(2) == '>' &&
							GetNextByte(3) == ' ')
					{
						Add(Token(TokenType::Arrow, 4));
						Skip(3);
						SkipSpaces();
					}
				}
				else if (GetCurrentByte() == '-')
				{
					Skip();
					if (GetCurrentByte() == '>' && GetNextByte() == ' ')
					{
						Add(Token(TokenType::Arrow, 2));
						Skip();
						SkipSpaces();
					}
				}
			}

			case '<':
				if (GetNextByte() == '<')
				{
					Skip(2);
					if (GetCurrentByte() == '<')
					{
						Add(Token(TokenType::RevTail, 3));
						Skip();
					}
					else
						Add(Token(TokenType::RevTail, 2));
				}
				break;

			case '$':
				Add(Token(TokenType::Dollar));
				Skip();
				SkipSpaces();
				ParseFunction();
				break;
		}
	}

	void Lexer::ParseFunction()
	{
		std::string symbol;

		while (IsValid() && IsValidSymbol())
		{
			symbol += GetCurrentByte();
			Skip();
		}

		if (symbol == "image")
		{
			Add(Token(TokenType::KwImage));
			SkipSpaces();
		}
		else if (symbol == "table")
		{
			Add(Token(TokenType::KwTable));
			SkipSpaces();
		}
		else if (symbol == "code")
		{
			Add(Token(TokenType::KwCode));
			SkipSpaces();
			mInCodeBlock = true;
		}
		else if (symbol == "admon")
		{
			Add(Token(TokenType::KwAdmon));
			SkipSpaces();
		}
		else if (symbol == "file")
		{
			Add(Token(TokenType::KwFile));
			SkipSpaces();
		}
		else if (symbol == "toc")
		{
			Add(Token(TokenType::KwToc));
			SkipSpaces();
		}
		else
			Add(Token(TokenType::Symbol, symbol));

		SkipSpaces();

		if (GetCurrentByte() == '\'')
			ParseQuotedText();
		else if (IsValidSymbol())
		{
			std::string symbol;
			while (IsValid() && IsValidSymbol())
			{
				symbol += GetCurrentByte();
				Skip();
			}
			Add(Token(TokenType::Symbol, symbol));
		}

		SkipSpaces();

		if (GetCurrentByte() == '{')
		{
			Add(Token(TokenType::LCurlyBracket));
			Skip();
		}
	}

	void Lexer::ParseInlineFunction()
	{
		switch (GetCurrentByte())
		{
			case ':':
				mInLink = true;
				Add(Token(TokenType::Colon));
				Skip();
				break;

			case '!':
				mInLink = true;
				Add(Token(TokenType::ExclamationMark));
				Skip();
				break;

			case '?':
				mInLink = true;
				Add(Token(TokenType::QuestionMark));
				Skip();
				break;
		}

		if (GetCurrentByte() == '\'')
			ParseQuotedText();
		else if (IsValidSymbol())
		{
			std::string symbol;
			while (IsValid() && IsValidSymbol())
			{
				symbol += GetCurrentByte();
				Skip();
			}
			Add(Token(TokenType::Symbol, symbol));
		}

		SkipSpaces();

		if (GetCurrentByte() == '{')
		{
			Add(Token(TokenType::LCurlyBracket));
			Skip();
		}
	}

	bool Lexer::IsValid()
	{
		return mBufferIndex < mBufferSize;
	}

	bool Lexer::IsValidText()
	{
		char c = GetCurrentByte();

		return (c >= 'A' && c <= 'Z') ||
			   (c >= 'a' && c <= 'z') ||
			   (c >= '0' && c <= '9') ||
			   c == ' ' || c == '-' || c == '.' ||
			   c == '!' || c == '?' ||
			   c == '"' || c == '\'' ||
			   c == ';' || c == ':';
	}

	bool Lexer::IsValidSymbol()
	{
		char c = GetCurrentByte();

		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
	}

	bool Lexer::IsValidNumeric()
	{
		char c = GetCurrentByte();

		return c >= '0' && c <= '9';
	}

	char Lexer::GetCurrentByte()
	{
		return mBuffer[mBufferIndex];
	}

	char Lexer::GetNextByte(size_t offset)
	{
		return mBufferIndex + offset < mBufferSize ? mBuffer[mBufferIndex + offset] : 0;
	}

	void Lexer::Skip(size_t offset)
	{
		mBufferIndex += offset;
	}

	void Lexer::SkipSpaces()
	{
		while (IsValid() && GetCurrentByte() == ' ')
			Skip();
	}

	void Lexer::Add(Token&& token)
	{
		mTokens.emplace_back(token);
	}
}
