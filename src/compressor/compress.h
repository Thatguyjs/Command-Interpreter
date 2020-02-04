#pragma once

#include <string>

#include "../../libs/file/file.h"


namespace Lang {
	class Compressor {
	public:

		// Get the last raised error
		std::string lastError();
		int lastErrorCode();

		// Load a file
		int load(const char* filepath);

		// Run the compressor
		int run();

	private:

		// Error handling
		void raiseError(int code, std::string message);

		std::string errorMessage = "";
		int errorCode;

		// File
		File file;
		std::string program = "";
		std::string resultProgram = "";

		// Program data
		int programIndex = 0;
		int programLength = 0;

		bool finished = false;
	};
}