#pragma once

#include <string>
#include <memory>
#include <stack>

namespace Gularen {
	enum class NodeGroup {
		document,

		text,
		fs,
		heading,
		paragraph,
		indent,
		break_,
		list,
		listItem,

		table,
		tableRow,
		tableCell,

		resource,

		code,

		punct,
		emoji,

		admon,

		footnoteJump,
		footnoteDescribe,
	};

	struct Node;

	using NodePtr = std::shared_ptr<Node>;
	using NodeChildren = std::vector<NodePtr>;

	struct Node {
		NodeGroup group;
		NodeChildren children;

		template<class T>
		const T& as() {
			return *static_cast<T*>(this);
		}

		virtual std::string toString() const;

		static std::string escape(const std::string& from);
	};

	struct DocumentNode : Node {
		std::string path;

		DocumentNode(const std::string& path);

		virtual std::string toString() const override;
	};

	struct TextNode : Node {
		std::string value;

		TextNode(const std::string& value);

		virtual std::string toString() const override;
	};
	
	enum class PunctType {
		hyphen,
		enDash,
		emDash,
		
		lsQuo,
		rsQuo,
		ldQuo,
		rdQuo,
	};

	struct PunctNode : Node {
		PunctType type;
		std::string value;

		PunctNode(PunctType type, const std::string& value);

		virtual std::string toString() const override;
	};

	struct EmojiNode : Node {
		std::string value;

		EmojiNode(const std::string& value);

		virtual std::string toString() const override;
	};
	
	enum class FSType {
		bold,
		italic,
		monospace
	};

	struct FSNode : Node {
		FSType type;

		FSNode(FSType type);

		virtual std::string toString() const override;
	};

	enum class HeadingType {
		chapter,
		section,
		subsection,
		subtitle,
	};

	struct HeadingNode : Node {
		HeadingType type;
		std::string id;

		HeadingNode(HeadingType type);

		virtual std::string toString() const override;
	};
	
	struct ParagraphNode : Node {
		ParagraphNode();

		virtual std::string toString() const override;
	};

	enum class AdmonType {
		note,
		hint,
		important,
		warning,
		danger,
		seeAlso
	};

	struct AdmonNode : Node {
		AdmonType type;

		AdmonNode(AdmonType type);

		virtual std::string toString() const override;
	};

	struct FootnoteJumpNode : Node {
		std::string value;

		FootnoteJumpNode(const std::string& value);

		virtual std::string toString() const override;
	};

	struct FootnoteDescribeNode : Node {
		std::string value;

		FootnoteDescribeNode(const std::string& value);

		virtual std::string toString() const override;
	};

	struct IndentNode : Node {
		IndentNode() {
			group = NodeGroup::indent;
		}

		virtual std::string toString() const override;
	};

	enum class BreakType {
		line,
		page,
	};

	struct BreakNode : Node {
		BreakType type;

		BreakNode(BreakType type);

		virtual std::string toString() const override;
	};

	enum class ListType {
		bullet,
		index,
		check,
	};

	struct ListNode : Node {
		ListType type;

		ListNode(ListType type);

		virtual std::string toString() const override;
	};

	enum class ListItemState {
		none,
		todo,
		done,
		canceled,
	};

	struct ListItemNode : Node {
		ListItemState state;
		size_t index;

		ListItemNode(size_t index);

		ListItemNode(size_t index, ListItemState state);

		virtual std::string toString() const override;
	};

	enum class Alignment {
		left = 0,
		center = 1,
		right = 2,
	};

	struct TableNode : Node {
		size_t header = 0;
		size_t footer = 0;
		std::vector<Alignment> alignments;

		TableNode();

		virtual std::string toString() const override;
	};

	struct TableRowNode : Node {
		TableRowNode();

		virtual std::string toString() const override;
	};

	struct TableCellNode : Node {
		TableCellNode() {
			group = NodeGroup::tableCell;
		}

		virtual std::string toString() const override;
	};

	enum class ResourceType {
		linker,
		linkerLocal,
		presenter,
		presenterLocal,
	};

	struct ResourceNode : Node {
		ResourceType type;
		std::string value;
		std::string id;
		std::string label;

		ResourceNode(ResourceType type, const std::string& value);

		virtual std::string toString() const override;
	};

	struct CodeNode : Node {
		std::string lang;
		std::string source;
		
		CodeNode() {
			group = NodeGroup::code;
		}

		virtual std::string toString() const override;
	};
}
