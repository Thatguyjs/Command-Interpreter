#include <iostream>
#include <string>

#include "interpreter/interpreter.h"
#include "compressor/compress.h"
#include "compiler/compiler.h"


int main(int argc, char** argv) {
	std::string filepath = "";
	std::string mode = "";

	
	if (argc > 2) {
		mode = argv[1];
		filepath = argv[2];
	}
	else {
		std::cout << "Displaying help\n\n" <<
			"-r filepath\t\tInterpret a file\n-run filepath\n\n" <<
			"-m filepath\t\tCompress a file (create a copy)\n-minify filepath\n\n" <<
			"-c filepath\t\tCompile a file (create a copy)\n-compile filepath\n";
		return 1;
	}


	if (mode == "-h" || mode == "-help") {
		std::cout << "Displaying help\n\n" <<
			"-r filepath\t\tInterpret a file\n-run filepath\n\n" <<
			"-m filepath\t\tCompress a file (create a copy)\n-minify filepath\n\n" <<
			"-c filepath\t\tCompile a file (create a copy)\n-compile filepath\n";
	}
	else if (mode == "-r" || mode == "-run") {
		Lang::Interpreter interpreter;

		if (interpreter.load(filepath.data())) {
			std::cout << "\n" << interpreter.lastError() << std::endl;
			return interpreter.lastErrorCode();
		}
		
		if (interpreter.run()) {
			std::cout << "\n" << interpreter.lastError() << std::endl;
			return interpreter.lastErrorCode();
		}
	}
	else if (mode == "-m" || mode == "-minify") {
		Lang::Compressor compressor;

		if (compressor.load(filepath.data())) {
			std::cout << "\n" << compressor.lastError() << std::endl;
			return compressor.lastErrorCode();
		}

		if (compressor.run()) {
			std::cout << "\n" << compressor.lastError() << std::endl;
			return compressor.lastErrorCode();
		}
	}
	else if (mode == "-c" || mode == "-compile") {
		Lang::Compiler compiler;

		if (compiler.load(filepath.data())) {
			std::cout << "\n" << compiler.lastError() << std::endl;
			return compiler.lastErrorCode();
		}

		if (compiler.run()) {
			std::cout << "\n" << compiler.lastError() << std::endl;
			return compiler.lastErrorCode();
		}
	}
	

	return 0;
}