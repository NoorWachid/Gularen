#include "TokenType.hpp"

namespace Gularen {

std::string ToString(TokenType type)
{
    switch (type) {
        case TokenType::Unknown: return "Unknown";

        case TokenType::DocumentBegin: return "DocumentBegin";
        case TokenType::DocumentEnd: return "DocumentEnd";

        case TokenType::Symbol: return "Symbol";
        case TokenType::Text: return "Text";
        case TokenType::QuotedText: return "QuotedText";

        case TokenType::Asterisk: return "Asterisk";
        case TokenType::Underline: return "Underline";
        case TokenType::Backtick: return "Backtick";

        case TokenType::Newline: return "Newline";
        case TokenType::Space: return "Space";

        case TokenType::Equal: return "Equal";
        case TokenType::Colon: return "Colon";
        case TokenType::QuestionMark: return "QuestionMark";
        case TokenType::ExclamationMark: return "ExclamationMark";

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

        case TokenType::Teeth: return "Teeth";

        default: return "[Unhandled]";
    }
}

}
