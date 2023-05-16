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

string InnerCode::createCodeforVar(string tempname, string op, varNode node1, varNode node2) {
	string result = tempname + " := ";
	if (node1.useAddress) {
		result += "*" + node1.name;
	}
	else {
		if (node1.num < 0) {
			result += node1.name;
		}
		else result += "var" + to_string(node1.num);
		result = (node1.num < 0) ? (result + node1.name) : (result + "var" + to_string(node1.num));
	}

	result += " " + op + " ";

	if (node2.useAddress) {
		result += "*" + node2.name;
	}
	else {
		if (node2.num < 0) {
			result += node2.name;
		}
		else result += "var" + to_string(node2.num);
	}

	return result;

}

string InnerCode::createCodeforAssign(varNode node1, varNode node2) {
	string result;
	if (node1.useAddress) {
		result = "*" + node1.name + " := ";
	}
	else {
		result = "var" + to_string(node1.num);
		result += " := ";
	}

	if (node2.useAddress) {
		result += "*" + node2.name;
	}
	else {
		if (node2.num < 0) {
			result += node2.name;
		}
		else result += "var" + to_string(node2.num);
	}
	

	return result;
}

string InnerCode::createCodeforParameter(varNode node) {
	string result = "PARAM ";
	result += "var" + to_string(node.num);
	return result;
}

string InnerCode::createCodeforArgRet(string form, varNode node) {
	string result = form;
	if (node.useAddress) {
		result += "*" + node.name;
	} 
	else {
		if (node.num < 0) {
			result += node.name;
		}
		else result += "var" + to_string(node.num);
	}
	
	return result;
}

string InnerCode::getNodeName(varNode node) {
	if (node.useAddress) {
		return "*" + node.name;
	}
	else {
		if (node.num < 0) {
			return node.name;
		}
		else return ("var" + to_string(node.num));
	}

}

string InnerCode::getarrayNodeName(arrayNode node) {
	return ("array" + to_string(node.num));
}