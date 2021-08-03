#include "TokenType.hpp"

namespace Gularen {

std::string ToString(TokenType type)
{
    switch (type) {
        case TokenType::Unknown: return "Unknown";

        case TokenType::DocumentBegin: return "DocumentBegin";
        case TokenType::DocumentEnd: return "DocumentEnd";

        case TokenType::Text: return "Text";
        case TokenType::Symbol: return "Symbol";

        case TokenType::Asterisk: return "Asterisk";
        case TokenType::Underline: return "Underline";
        case TokenType::Backtick: return "Backtick";

        case TokenType::Newline: return "Newline";
        case TokenType::Space: return "Space";

        case TokenType::Equal: return "Equal";

        case TokenType::LCurlyBracket: return "LCurlyBracket";
        case TokenType::RCurlyBracket: return "RCurlyBracket";

        case TokenType::Box: return "Box";

        case TokenType::Bullet: return "Bullet";
        case TokenType::NBullet: return "NBullet";
        case TokenType::CheckBox: return "CheckBox";
        case TokenType::Line: return "Line";

        case TokenType::Anchor: return "Anchor";

        case TokenType::Tail: return "Tail";
        case TokenType::RevTail: return "RevTail";
        case TokenType::Arrow: return "Arrow";

        default: return "[Unhandled]";
    }
}

}
