#ifndef _AST_HPP_
#define _AST_HPP_

#include <string>
#include <vector>
using namespace std;
namespace AST {
	class Node;

	enum NodeType{
		NODE_TYPE_CONST_CHAR,
		NODE_TYPE_CONST_INTEGER,
		NODE_TYPE_CONST_FLOAT,
		NODE_TYPE_CONST_STRING,
		NODE_TYPE_IDENTIFIER,

	};

	union Value {
		int VALUE_INTERGER;
		float VALUE_FLOAT;
		double VALUE_DOUBLE;
		char VALUE_CHAR;
		void* VALUE_POINTER;
		string* VALUE_STRING;
	};

	class Node {
		public:
			NodeType nodeType;
			string name; /* 仅 IDENTIFIER 使用 */
			Value value;

			vector<Node*> children;

			Node(NodeType nodeType_, string name_, Value value_): nodeType(nodeType_), name(name_), value(value_) {}
			
			template<typename T, typename... Children>
			void addChildren(T& child_, Children... children_) {
				children.push_back(child_);
				addChildren(children_);
			}
	};
}

#endif