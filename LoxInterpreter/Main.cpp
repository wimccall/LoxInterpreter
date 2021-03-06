// LoxInterpreter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Lox.h"

bool Lox::hadError = false;

int main(int argc, char** argv)
{
	int count;
	// Display each command-line argument.  
	std::cout << "\nCommand-line arguments:\n";
	std::cout << "Count: " << argc << "\n";
	for (count = 0; count < argc; count++)
		std::cout << "  argv[" << count << "]   "
		<< argv[count] << "\n";

	if (argc > 2) {
		std::cout << "Usage: LoxInterpreter [script]";
		exit(64);
	} else if (argc == 2) {
		Lox::runFile(argv[1]);
	} else {
		Lox::runPrompt();
	}
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
