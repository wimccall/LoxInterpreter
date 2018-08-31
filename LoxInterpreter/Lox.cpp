#include "pch.h"
#include "Lox.h"

void Lox::runFile(std::string path) {

	// Open file and get filesize
	std::ifstream file(path);
	std::string source;
	hadError = false;
	if (file.is_open()) {
		// Get file contents
		source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		// print out the contents of the file
		#ifndef NDEBUG
		std::cout << "\nsource:\n" << source << "\n------------\n";
		#endif
	} else {
		std::cout << "cannot open file: " << path  << "\n";
	};
	
	run(source);

	// Indicate an error in the exit code.           
	if (hadError) exit(65);
}


void Lox::runPrompt() {
	hadError = false;
	while (1) {
		std::string newInput;
		std::cout << "\n> ";
		std::getline(std::cin, newInput);
		run(newInput);
		hadError = false;
	}
}

void Lox::run(std::string source) {
	Scanner scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();

	for (Token token : tokens) std::cout << token.toString() << "\n";
}

void Lox::error(int line, std::string message) {
	report(line, "", message);
}

void Lox::report(int line, std::string sWhere, std::string message) {
	std::cout << "[line " << line << "] Error" << sWhere << ": " << message;
	hadError = true;
}
