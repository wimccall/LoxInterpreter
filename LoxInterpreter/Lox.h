#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Scanner.h"

class Lox
{
public:
	static void runFile(std::string path);
	static void runPrompt();
	static void error(int line, std::string message);

private:
	static bool hadError;
	static void run(std::string source);
	static void report(int line, std::string sWhere, std::string message);
};

