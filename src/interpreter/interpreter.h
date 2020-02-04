#pragma once

#include <string>

#include "../../libs/convert/char.h"
#include "../../libs/file/file.h"
#include "../../libs/list/list.h"

#include "jump.h"


namespace Lang {
	class Interpreter {
	public:

		// Get the last raised error
		std::string lastError();
		int lastErrorCode();

		// Load a file
		int load(const char* filepath);

		// Run the interpreter
		int run();

	private:
		
		// Error handling
		void raiseError(int code, std::string message);
		void raiseError(int code, std::string message, int index);

		std::string errorMessage = "";
		int errorCode = 0;
		
		// The local file
		File file;
		std::string program = "";

		// Type conversion
		CharConvert converter;


		// Program functions
		char getProgramChar();
		void changeProgramIndex(int amount);

		int getCellValue();
		void changeCellPointer(int amount);
		void changeCellValue(int amount);

		bool compareValue();

		void createJump();
		void gotoJump();


		// Program stats
		int programIndex = 0;
		long int programLength = 0;

		char memory[30000] = { 0 };
		int memoryPointer = 0;
		LinkedList<Jump> jumps;

		bool finished = false;
	};
}