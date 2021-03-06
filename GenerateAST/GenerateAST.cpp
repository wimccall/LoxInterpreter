// GenerateAST.cpp : This file generates our tedious expression classes for us so we can make changes without 
//		mucking through changing dozens of lines of boilerplate. We only need to change their string representation
//		in main of this file.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
static inline std::string trim(std::string s) {
	ltrim(s);
	rtrim(s);
	return s;
}

static inline std::vector<std::string> trimAll(std::vector<std::string> s) {
	std::vector<std::string> ret;
	for (std::string a : s) {
		ret.push_back(trim(a));
	}
	return ret;
}

std::vector<std::string> split(const std::string s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::string toLower(std::string data) {
	std::string s = data;
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(data[i]);
	}
	return s;
}

static void defineType(std::ofstream &writer, std::string baseName, std::string className, std::string fieldList) {
	writer << "template <class T>\nclass " + className + " : public " + baseName + "<T> {\n";
	
	writer << "public:\n";
	// Constructor.                                              
	writer << "   " + className + "(" + fieldList + "):\n";

	// Store parameters in fields. Constructor, cont.                               
	std::vector<std::string> fields = trimAll(split(fieldList,','));
	for (int i = 0; i < fields.size(); i++) {
		std::string field = fields[i];
		std::string name = trim(split(field, ' ')[1]);
		writer << "      " + name + "(" + name + ")";
		if (i != fields.size() - 1) writer << ",";
		writer << "\n";
	}
	writer << "      {}\n\n"; // End constructor

	// Visitor pattern
	writer << "\n   T accept(Visitor<T> *visitor) {\n";
	writer << "      return visitor->visit" + className + baseName + "(this);\n";
	writer << "   }\n";

	// Fields
	for (std::string field : fields) {
		writer << "   " + trim(split(field, ' ')[0]) + " " + trim(split(field, ' ')[1]) + ";\n";
	}

	writer << "};\n";
}

static void defineVisitor(std::ofstream& writer, std::string baseName, std::vector<std::string> types) {
	writer << "template<class T>\nclass Visitor {\npublic:\n";
	for (std::string type : types) {
		std::string typeName = trim(split(type, ':')[0]);
		writer << "   virtual T visit" + typeName + baseName + "(" + typeName + "<T>* " + toLower(baseName) + ") = 0;\n";
	}
	writer << "};\n";
}

void defineAst(std::string out, std::string baseName, std::vector<std::string> types) {
	std::string path = out + "/" + baseName + ".h";
	std::ofstream myfile;
	myfile.open(path);

	myfile << "#include <vector>\n#include <iostream>\n#include \"Token.h\"\n";
	myfile << "template <class T>\nclass Visitor;\n";
	myfile << "template <class T>\n";
	myfile << "class " << baseName.c_str() << " {\npublic:\n";
	myfile << "   virtual T accept(Visitor<T> *visitor) = 0;\n";
	myfile << "};\n\n";
	// Define the subclasses based on the hard-coded strings in main.
	for (std::string type : types) {
		std::string className = trim(split(type, ':')[0]);
		std::string fields = trim(split(type, ':')[1]);
		defineType(myfile, baseName, className, fields);
	}

	// define the visitors for each class
	defineVisitor(myfile, baseName, types);
	myfile.close();
}

int main(int argc,char** argv)
{
	if (argc != 2) {
		std::cout << "Usage: GenerateAST <output_directory>";
	}
	std::string outputDir = argv[1];
	defineAst(outputDir, "Expr", std::vector<std::string>{
		"Binary   : Expr<T>* left, Token op, Expr<T>* right",
		"Grouping : Expr<T>* expression",
		"Literal  : Object* value",
		"Unary    : Token op, Expr<T>* right"
	});
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
