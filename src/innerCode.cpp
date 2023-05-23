#include "innerCode.h"
#include "codeOptimize.h"
#include <fstream>

InnerCode::InnerCode() {

}

void InnerCode::addCode(string str) {
	codeList.push_back(str);
}

void InnerCode::printCode() {

	Optimize optimize(codeList);
	codeList = optimize.getCodeList();
	ofstream out("innerCode.txt");

	cout << "\n===============INNERCODE===============" << endl;
	for (string s : codeList) {
		cout << s << endl;
		out << s << "\n";
	}
}

string InnerCode::createCode(string tempname, string op, Node node1, Node node2) {
	string result = tempname + " := ";

	if (node1.retUseAdd()) {
		result += "*" + node1.retName();
	}
	else {
		if (node1.retNum() < 0) {
			result += node1.retName();
		}
		else result += "var" + to_string(node1.retNum());
		result = (node1.retNum() < 0) ? (result + node1.retName()) : (result + "var" + to_string(node1.retNum()));
	}

	result += " " + op + " ";

	if (node2.retUseAdd()) {
		result += "*" + node2.retName();
	}
	else {
		if (node2.retNum() < 0) {
			result += node2.retName();
		}
		else result += "var" + to_string(node2.retNum());
	}

	return result;

}

string InnerCode::createCode(Node node1, Node node2) {
	string result;
	if (node1.retUseAdd()) {
		result = "*" + node1.retName() + " := ";
	}
	else {
		result = "var" + to_string(node1.retNum());
		result += " := ";
	}

	if (node2.retUseAdd()) {
		result += "*" + node2.retName();
	}
	else {
		if (node2.retNum() < 0) {
			result += node2.retName();
		}
		else result += "var" + to_string(node2.retNum());
	}
	

	return result;
}

string InnerCode::createCode(Node node) {
	string result = "PARAM ";
	result += "var" + to_string(node.retNum());
	return result;
}

string InnerCode::createCode(string form, Node node) {
	string result = form;
	if (node.retUseAdd()) {
		result += "*" + node.retName();
	} 
	else {
		if (node.retNum() < 0) {
			result += node.retName();
		}
		else result += "var" + to_string(node.retNum());
	}
	
	return result;
}

string InnerCode::getNodeName(Node node) {
	if (node.retUseAdd()) {
		return "*" + node.retName();
	}
	else {
		if (node.retNum() < 0) {
			return node.retName();
		}
		else return ("var" + to_string(node.retNum()));
	}

}

string InnerCode::getarrayNodeName(Node node) {
	return ("array" + to_string(node.retNum()));
}