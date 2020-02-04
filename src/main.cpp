#include <iostream>
#include <string>

#include "interpreter/interpreter.h"
#include "compressor/compress.h"


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
			"-c filepath\t\tCompress a file (create a copy)\n-compress filepath\n";
		return 1;
	}


	if (mode == "-h" || mode == "-help") {
		std::cout << "Displaying help\n\n" <<
			"-r filepath\t\tInterpret a file\n-run\n\n" <<
			"-c filepath\t\tCompress a file (create a copy)\n-compress filepath\n";
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
	else if (mode == "-c" || mode == "-compress") {
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
	

	return 0;
}