#pragma once

#include "Gularen/Frontend/Node.hpp"
#include <cstdint>

namespace Gularen {
namespace Json {

class Composer {
public:
	std::string_view compose(Document* document) {
		_content = "{\"kind\":\"document\"";

		if (document->annotations.size() != 0) {
			_content.append(",\"annotations\":{");

			for (size_t i = 0; i < document->annotations.size(); i += 1) {
				if (i != 0) {
					_content.append(",");
				}
				_content.append("\"");
				_escape(document->annotations[i].key);
				_content.append("\":\"");
				_escape(document->annotations[i].value);
				_content.append("\"");
			}

			_content.append("}");
		}

		if (!document->children.empty()) {
			_content.append(",\"children\":[");

			if (document != nullptr) {
				for (size_t i = 0; i < document->children.size(); i += 1) {
					if (i != 0) {
						_content.append(",");
					}
					_compose(document->children[i]);
				}
			}

			_content.append("]");
		}

		_content.append("}");

		return std::string_view(_content.data(), _content.size());
	}

private:
	void _compose(const Node* node) {
		_content.append("{");
		switch (node->kind) {
			case NodeKind::comment: {
				_content.append("\"kind\":\"comment\",\"content\":\"");
				_escape(static_cast<const Comment*>(node)->content);
				_content.append("\"");
				break;
			}
			case NodeKind::paragraph: {
				_content.append("\"kind\":\"paragraph\"");
				break;
			}
			case NodeKind::text: {
				_content.append("\"kind\":\"text\",\"content\":\"");
				_escape(static_cast<const Text*>(node)->content);
				_content.append("\"");
				break;
			}
			case NodeKind::space: {
				_content.append("\"kind\":\"space\"");
				break;
			}
			case NodeKind::punct: {
				_content.append("\"kind\":\"punct\",\"type\":\"");
				switch (static_cast<const Punct*>(node)->type) {
					case Punct::Type::hypen:
						_content.append("hyphen");
						break;
					case Punct::Type::enDash:
						_content.append("enDash");
						break;
					case Punct::Type::emDash:
						_content.append("emDash");
						break;
					case Punct::Type::quoteOpen:
						_content.append("quoteOpen");
						break;
					case Punct::Type::quoteClose:
						_content.append("quoteClose");
						break;
					case Punct::Type::squoteOpen:
						_content.append("squoteOpen");
						break;
					case Punct::Type::squoteClose:
						_content.append("squoteClose");
						break;
				}
				_content.append("\"");
				break;
			}
			case NodeKind::emphasis: {
				_content.append("\"kind\":\"emphasis\",\"type\":\"");
				switch (static_cast<const Emphasis*>(node)->type) {
					case Emphasis::Type::bold:
						_content.append("bold");
						break;
					case Emphasis::Type::italic:
						_content.append("italic");
						break;
					case Emphasis::Type::underline:
						_content.append("underline");
						break;
				}
				_content.append("\"");
				break;
			}
			case NodeKind::highlight: {
				_content.append("\"kind\":\"highlight\"");
				break;
			}
			case NodeKind::change: {
				_content.append("\"kind\":\"change\",\"type\":\"");
				switch (static_cast<const Change*>(node)->type) {
					case Change::Type::added:
						_content.append("added");
						break;
					case Change::Type::removed:
						_content.append("removed");
						break;
				}
				_content.append("\"");
				break;
			}
			case NodeKind::lineBreak: {
				_content.append("\"kind\":\"lineBreak\"");
				break;
			}
			case NodeKind::pageBreak: {
				_content.append("\"kind\":\"pageBreak\"");
				break;
			}
			case NodeKind::dinkus: {
				_content.append("\"kind\":\"dinkus\"");
				break;
			}
			case NodeKind::quote: {
				_content.append("\"kind\":\"quote\"");
				break;
			}
			case NodeKind::heading: {
				switch (static_cast<const Heading*>(node)->type) {
					case Heading::Type::chapter: 
						_content.append("\"kind\":\"heading\",\"type\":\"chapter\"");
						break;
					case Heading::Type::section:
						_content.append("\"kind\":\"heading\",\"type\":\"section\"");
						break;
					case Heading::Type::subsection:
						_content.append("\"kind\":\"heading\",\"type\":\"subsection\"");
						break;
				}
				break;
			}
			case NodeKind::title: {
				_content.append("\"kind\":\"title\"");
				break;
			}
			case NodeKind::subtitle: {
				_content.append("\"kind\":\"subtitle\"");
				break;
			}
			case NodeKind::list: {
				_content.append("\"kind\":\"list\"");
				break;
			}
			case NodeKind::numberedList: {
				_content.append("\"kind\":\"numberedList\"");
				break;
			}
			case NodeKind::item: {
				_content.append("\"kind\":\"item\"");
				break;
			}
			case NodeKind::checkList: {
				_content.append("\"kind\":\"checkList\"");
				break;
			}
			case NodeKind::checkItem: {
				_content.append("\"kind\":\"checkItem\",\"checked\":");
				_content.append(static_cast<const CheckItem*>(node)->checked ? "true" : "false");
				break;
			}
			case NodeKind::definitionList: {
				_content.append("\"kind\":\"definitionList\"");
				break;
			}
			case NodeKind::definitionItem: {
				_content.append("\"kind\":\"definitionItem\"");
				break;
			}
			case NodeKind::definitionTerm: {
				_content.append("\"kind\":\"definitionTerm\"");
				break;
			}
			case NodeKind::definitionDesc: {
				_content.append("\"kind\":\"definitionDesc\"");
				break;
			}
			case NodeKind::code: {
				auto code = static_cast<const Code*>(node);

				_content.append("\"kind\":\"code\",\"label\":\"");
				_escape(code->label);
				_content.append("\",\"content\":\"");
				_escape(code->content);
				_content.append("\"");
				break;
			}
			case NodeKind::codeBlock: {
				auto code = static_cast<const CodeBlock*>(node);

				_content.append("\"kind\":\"codeBlock\",\"label\":\"");
				_escape(code->label);
				_content.append("\",\"content\":\"");
				_escape(code->content);
				_content.append("\"");
				break;
			}
			case NodeKind::table: {
				_content.append("\"kind\":\"table\"");
				break;
			}
			case NodeKind::row: {
				_content.append("\"kind\":\"row\"");
				break;
			}
			case NodeKind::cell: {
				_content.append("\"kind\":\"cell\"");
				break;
			}
			case NodeKind::admonition: {
				auto admon = static_cast<const Admonition*>(node);
				_content.append("\"kind\":\"admon\",\"label\":\"");
				_escape(admon->label);
				_content.append("\"");
				break;
			}
			case NodeKind::dateTime: {
				auto dateTime = static_cast<const DateTime*>(node);
				_content.append("\"kind\":\"dateTime\"");
				if (dateTime->date.size() != 0) {
					_content.append(",\"date\":\"");
					_escape(dateTime->date);
					_content.append("\"");
				}
				if (dateTime->time.size() != 0) {
					_content.append(",\"time\":\"");
					_escape(dateTime->time);
					_content.append("\"");
				}
				break;
			}
			case NodeKind::accountTag: {
				auto tag = static_cast<const AccountTag*>(node);
				_content.append("\"kind\":\"accountTag\",\"resource\":\"");
				_escape(tag->resource);
				_content.append("\"");
				break;
			}
			case NodeKind::hashTag: {
				auto tag = static_cast<const AccountTag*>(node);
				_content.append("\"kind\":\"hashTag\",\"resource\":\"");
				_escape(tag->resource);
				_content.append("\"");
				break;
			}
			case NodeKind::link: {
				auto link = static_cast<const Link*>(node);
				_content.append("\"kind\":\"link\"");
				if (link->resource.size() != 0) {
					_content.append(",\"resource\":\"");
					_escape(link->resource);
					_content.append("\"");
				}
				if (link->headings.size() != 0) {
					_content.append(",\"headings\":[");
					for (size_t i = 0; i < link->headings.size(); i += 1) {
						if (i != 0) {
							_content.append(",");
						}
						_content.append("\"");
						_escape(link->headings[i]);
						_content.append("\"");
					}
					_content.append("]");
				}
				if (link->label.size() != 0) {
					_content.append(",\"label\":\"");
					_escape(link->label);
					_content.append("\"");
				}
				break;
			}
			case NodeKind::view: {
				auto view = static_cast<const View*>(node);
				_content.append("\"kind\":\"view\"");
				if (view->resource.size() != 0) {
					_content.append(",\"resource\":\"");
					_escape(view->resource);
					_content.append("\"");
				}
				if (view->label.size() != 0) {
					_content.append(",\"label\":\"");
					_escape(view->label);
					_content.append("\"");
				}
				break;
			}
			case NodeKind::document: {
				_content.append("\"kind\":\"document\"");
				break;
			}
			case NodeKind::footnote: {
				auto footnote = static_cast<const Footnote*>(node);
				_content.append("\"kind\":\"footnote\",\"desc\":\"");
				_escape(footnote->desc);
				_content.append("\"");
				break;
			}
			case NodeKind::emoji: {
				auto emoji = static_cast<const Emoji*>(node);
				_content.append("\"kind\":\"emoji\",\"code\":\"");
				_escape(emoji->code);
				_content.append("\"");
				break;
			}
			case NodeKind::inText: {
				auto citation = static_cast<const InText*>(node);
				_content.append("\"kind\":\"inText\",\"id\":\"");
				_escape(citation->id);
				_content.append("\"");
				break;
			}
			case NodeKind::reference: {
				auto reference = static_cast<const Reference*>(node);
				_content.append("\"kind\":\"reference\",\"id\":\"");
				_escape(reference->id);
				_content.append("\"");
				break;
			}
			case NodeKind::referenceInfo: {
				auto info = static_cast<const ReferenceInfo*>(node);
				_content.append("\"kind\":\"referenceInfo\",\"key\":\"");
				_escape(info->key);
				_content.append("\"");
				break;
			}
			default: {
				_content.append("\"kind\":\"unknown\"");
				break;
			}
		}

		_content.append(",\"range\":[");
		_content.append(std::to_string(node->range.startLine));
		_content.append(",");
		_content.append(std::to_string(node->range.startColumn));
		_content.append(",");
		_content.append(std::to_string(node->range.endLine));
		_content.append(",");
		_content.append(std::to_string(node->range.endColumn));
		_content.append("]");

		if (node->annotations.size() != 0) {
			_content.append(",\"annotations\":{");

			for (size_t i = 0; i < node->annotations.size(); i += 1) {
				if (i != 0) {
					_content.append(",");
				}
				_content.append("\"");
				_escape(node->annotations[i].key);
				_content.append("\":\"");
				_escape(node->annotations[i].value);
				_content.append("\"");
			}

			_content.append("}");
		}

		if (node->children.size() != 0) {
			_content.append(",\"children\":[");

			for (size_t i = 0; i < node->children.size(); i += 1) {
				if (i != 0) {
					_content.append(",");
				}
				_compose(node->children[i]);
			}

			_content.append("]");
		}

		_content.append("}");
	}

	void _escape(std::string_view content) {
		size_t i = 0;
		while (i < content.size()) {
			unsigned char byte = content[i];
			switch (byte) {
				case '"':
					_content.append("\\\"");
					i += 1;
					break;
				case '\\':
					_content.append("\\\\");
					i += 1;
					break;
				case '/':
					_content.append("\\/");
					i += 1;
					break;
				case 8:
					_content.append("\\b");
					i += 1;
					break;
				case 12:
					_content.append("\\f");
					i += 1;
					break;
				case '\r':
					_content.append("\\r");
					i += 1;
					break;
				case '\n':
					_content.append("\\n");
					i += 1;
					break;
				case '\t':
					_content.append("\\t");
					i += 1;
					break;

				default: {
					if (byte >= ' ' && byte <= '~') {
						_content.append(1, byte);
						i += 1;
					} else {
						unsigned int codepoint = 0;

						if ((byte & 0b10000000) == 0b00000000) {
							// Single-bytes
							codepoint = byte;
							i += 1;
						} else if ((i + 1) < content.size() && (byte & 0b11100000) == 0b11000000) {
							// Two-bytes
							codepoint = ((byte & 0b00011111) << 6) | (content[i + 1] & 0b00111111);
							i += 2;
						} else if ((i + 2) < content.size() && (byte & 0b11110000) == 0b11100000) {
							// Three-bytes
							codepoint = 
								((byte & 0b00001111) << 12) | 
								((content[i + 1] & 0b00111111) << 6) |
								(content[i + 2] & 0b00111111);
							i += 3;
						} else if ((i + 3) < content.size() && (byte & 0b11111000) == 0b11110000) {
							// Four-bytes
							codepoint = 
								((byte & 0b00000111) << 18) | 
								((content[i + 1] & 0b00111111) << 12) |
								((content[i + 2] & 0b00111111) << 6) | 
								(content[i + 3] & 0b00111111);
							i += 4;
						} else {
							codepoint = byte;
							i += 1;
						}

						_content.append("\\u");
						_content.append(_toHexString(static_cast<uint16_t>(codepoint)));
					}
					break;
				}
			}
		}
	}

	template <typename I> 
	std::string _toHexString(I w, size_t length = sizeof(I)<<1) {
		static const char* digits = "0123456789ABCDEF";
		std::string rc(length, '0');
		for (size_t i = 0, j = (length - 1) * 4 ; i < length; ++i, j -= 4) {
			rc[i] = digits[(w>>j) & 0x0f];
		}
		return rc;
	}

private:
	std::string _content;
};

}
}


