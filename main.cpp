#include <iostream>

#include "src/interpreter.h"


int main(int argc, char** argv) {
	const char* filepath = "";

	
	if (argc > 1) filepath = argv[1];
	else {
		std::cout << "Enter a filepath to run";
		return 1;
	}


	Lang::Interpreter interpreter;
	
	if (interpreter.load(filepath) != 0) {
		std::cout << "\n" << interpreter.lastError() << std::endl;
		return interpreter.lastErrorCode();
	}

	int result = interpreter.run();

	if (result != 0) {
		std::cout << "\n" << interpreter.lastError() << std::endl;
		std::cout << "Exiting with code " << interpreter.lastErrorCode() << std::endl;
		return interpreter.lastErrorCode();
	}


	return 0;
}