#pragma once

#include <string>

#include "../../libs/file/file.h"


namespace Lang {
	class Compiler {
	public:

		// Get the last raised error
		std::string lastError();
		int lastErrorCode();

		// Load a file
		int load(const char* filepath);

		// Run the compiler
		int run();

	private:

		// Error handling
		void raiseError(int code, std::string message);

		std::string errorMessage = "";
		int errorCode = 0;

		// Compiling commands
		void addDebug();
		void addStatement();
		void addJump();
		void gotoJump();
		void addFunction(const char* data);

		// File
		File file;
		std::string programName = "";
		std::string program = "";
		std::string result = ""; // The program to write to disk

		// Program data
		int programIndex = 0;
		int programLength = 0;

		bool finished = false;
	};
}