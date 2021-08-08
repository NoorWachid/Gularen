#include "Lexer.hpp"
#include "IO.hpp"

namespace Gularen {

Lexer::Lexer()
{
    Reset();
}

void Lexer::SetBuffer(const std::string& buffer)
{
    this->buffer = buffer;
    bufferSize = buffer.size();

    Reset();
}

void Lexer::SetTokens(const std::vector<Token> &tokens)
{
    Reset();
    buffer.clear();

    this->tokens = tokens;
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

            case '\n':
            {
                size_t size = 0;
                while (IsValid() && GetCurrentByte() == '\n')
                {
                    ++size;
                    Skip();
                }

                if (!tokens.empty() && tokens.back().type == TokenType::Newline)
                    tokens.back().size += size;
                else
                {
                    Token token(TokenType::Newline);
                    token.size = size;
                    Add(std::move(token));
                }

                ParseNewline();
                break;
            }

            case '^':
                while (IsValid() && GetCurrentByte() != '\n')
                    Skip();
                break;

            case '>':
                if (inHeaderLine)
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

            default:
                if (IsValidText())
                    ParseText();
                else
                    Skip(); // Unhandled symbols
                break;
        }
    }

    Add(Token(TokenType::DocumentEnd));
}

std::string Lexer::GetBuffer()
{
    return buffer;
}

Token &Lexer::GetToken(size_t index)
{
    return tokens[index];
}

void Lexer::Reset()
{
    inHeaderLine = false;
    inLink = false;
    bufferIndex = 0;
    tokens.clear();
}

std::vector<Token>& Lexer::GetTokens()
{
    return tokens;
}

std::string Lexer::GetTokensAsString()
{
    std::string buffer;

    for (Token& token: tokens)
        buffer += token.ToString() + "\n";

    return buffer + "\n";
}

void Lexer::ParseText()
{
    Token token;
    token.type = TokenType::Text;

    while (IsValid() && IsValidText())
    {
        token.value += GetCurrentByte();
        Skip();
    }

    Add(std::move(token));
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

void Lexer::ParseRepeat(char c, TokenType type)
{
    Token token(type);
    token.size = 1;
    Skip();

    while (IsValid() && GetCurrentByte() == c)
    {
        ++token.size;
        Skip();
    }

    Add(std::move(token));
}

void Lexer::ParseNewline()
{
    // State variables
    inHeaderLine = false;

    switch (GetCurrentByte())
    {
        case ' ':
            ParseRepeat(' ', TokenType::Space);
            ParseNewline();
            break;

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
                Add(Token(TokenType::Line));
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
                Add(Token(TokenType::Text, buffer));

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
            if ((GetNextByte(1) == ' ' || GetNextByte(1) == '+') && GetNextByte(2) == ']')
            {
                Token token(TokenType::CheckBox);
                if (GetNextByte(1) == '+')
                    token.size = 1;

                Add(std::move(token));
                Skip(3);
                SkipSpaces();
            }
            break;

        case '>':
        {
            inHeaderLine = true;

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
                else if (GetCurrentByte() == '-' && GetNextByte(1) == '-' && GetNextByte(2) == '>' && GetNextByte(3) == ' ')
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

        case ':':
            if (GetNextByte() == ':')
            {
                Add(Token(TokenType::Box));
                Skip(2);
                SkipSpaces();
                ParseFunction();
            }
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
    Add(Token(TokenType::Symbol));
    SkipSpaces();
}

void Lexer::ParseInlineFunction()
{
    switch (GetCurrentByte())
    {
        case ':':
            inLink = true;
            Add(Token(TokenType::Colon));
            Skip();
            break;

        case '!':
            inLink = true;
            Add(Token(TokenType::ExclamationMark));
            Skip();
            break;

        case '?':
            inLink = true;
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
    return bufferIndex < bufferSize;
}

bool Lexer::IsValidText()
{
    char c = GetCurrentByte();

    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
            c == ' ' || c == '-' ||
            c == ',' || c == '.' ||
            c == '!' || c == '?' ||
            c == '\'' || c == '"' ||
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
    return buffer[bufferIndex];
}

char Lexer::GetNextByte(size_t offset)
{
    return bufferIndex + offset < bufferSize ? buffer[bufferIndex + offset] : 0;
    }

    void Lexer::Skip(size_t offset)
    {
    bufferIndex += offset;
}

void Lexer::SkipSpaces()
{
    while (IsValid() && GetCurrentByte() == ' ')
        Skip();
}

void Lexer::Add(Token&& token)
{
    tokens.emplace_back(token);
}

}
