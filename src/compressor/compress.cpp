#include <iostream>

#include "compress.h"


namespace Lang {

	// Error handling
	void Compressor::raiseError(int code, std::string message) {
		this->errorCode = code;
		this->errorMessage = message;
	}

	std::string Compressor::lastError() {
		return this->errorMessage;
	}

	int Compressor::lastErrorCode() {
		return this->errorCode;
	}


	// Load a file
	int Compressor::load(const char* filepath) {
		this->file.load(filepath);

		if (this->file.read() == "") {
			this->raiseError(1, "Error opening file\n");
			return 1;
		}

		this->program = this->file.data();
		this->programLength = this->program.length();
		return 0;
	}


	// Run the compressor
	int Compressor::run() {
		while (this->errorCode == 0 && !this->finished) {
			char current = this->program[this->programIndex];


			switch (current) {

				// Remove comments
				case '\"':
					this->programIndex++;

					while (this->program[this->programIndex] != '\"') {
						this->programIndex++;
					}

					this->programIndex++;
					break;

				case '/':
					while (this->program[this->programIndex] && this->program[this->programIndex] != '\n') {
						this->programIndex++;
					}

					this->programIndex++;
					break;


				// Don't format certain statements
				case '?':
					while (this->program[this->programIndex] != '(') {
						this->resultProgram += this->program[this->programIndex];
						this->programIndex++;
					}
					break;

				case '{':
					while (this->program[this->programIndex] != '}') {
						this->resultProgram += this->program[this->programIndex];
						this->programIndex++;
					}
					break;


				// Remove whitespace
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					this->programIndex++;
					break;


				// Add the current character
				default:
					this->resultProgram += this->program[this->programIndex];
					this->programIndex++;
					break;

			}


			if (this->programIndex >= this->programLength) {
				this->finished = true;
			}
		}

		std::cout << "Finished compressing" << std::endl;

		// Generate new file path
		std::string newName = this->file.path();
		int newNameIndex = 0;

		std::string newPath = "";

		while (newName[newNameIndex] != '.') {
			newPath += newName[newNameIndex];
			newNameIndex++;
		}

		newPath += "_compressed";

		while (newName[newNameIndex]) {
			newPath += newName[newNameIndex];
			newNameIndex++;
		}

		std::cout << "Writing file..." << std::endl;

		// Write file
		this->file.load(newPath.data());
		this->file.write(this->resultProgram.data());

		if (this->file.error) {
			this->raiseError(1, "Error writing to file");
		}

		std::cout << "Done" << std::endl;

		return 0;
	}

}