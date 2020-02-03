#include <iostream>

#include "interpreter.h"


namespace Lang {

	void Interpreter::raiseError(int code, std::string message) {
		this->errorCode = code;
		this->errorMessage = message;
	}

	void Interpreter::raiseError(int code, std::string message, int index) {
		this->errorCode = code;
		this->errorMessage = message + (std::string) " at index " + std::to_string(index);
	}

	std::string Interpreter::lastError() {
		return this->errorMessage;
	}

	int Interpreter::lastErrorCode() {
		return this->errorCode;
	}


	int Interpreter::load(const char* filepath) {
		this->file.load(filepath);
		
		if (this->file.read() == "") {
			this->raiseError(1, "Error opening file\n");
			return 1;
		}

		this->program = this->file.data();
		this->programLength = this->program.length();
		return 0;
	}


	// Program functions

	
	char Interpreter::getProgramChar() {
		return this->program[this->programIndex];
	}

	void Interpreter::changeProgramIndex(int amount) {
		int newValue = this->programIndex + amount;

		if (newValue < 0) {
			this->raiseError(1, "Program index out of range");
		}
		else if (newValue >= this->programLength) {
			this->finished = true;
		}
		else {
			this->programIndex = newValue;
		}
	}


	int Interpreter::getCellValue() {
		return this->memory[this->memoryPointer];
	}

	void Interpreter::changeCellPointer(int amount) {
		int newValue = this->memoryPointer + amount;

		if (newValue < 0 || newValue >= 30000) {
			this->raiseError(1, "Cell pointer out of range");
		}
		else {
			this->memoryPointer = newValue;
		}
	}

	void Interpreter::changeCellValue(int amount) {
		int newValue = this->getCellValue() + amount;

		if (newValue < -127 || newValue > 127) {
			this->raiseError(1, "Cell value out of range");
		}
		else {
			this->memory[this->memoryPointer] = newValue;
		}
	}


	bool Interpreter::compareValue() {
		// Skip whitespace
		bool skip = true;

		while (!this->finished && skip) {
			switch (this->getProgramChar()) {

				case ' ':
				case '\t':
				case '\r':
				case '\n':
					this->changeProgramIndex(1);
					break;

				default:
					skip = false;

			}
		}

		// Get comparison
		std::string comparison = "";

		while (!this->finished && this->getProgramChar() != ' ') {
			comparison += this->getProgramChar();
			this->changeProgramIndex(1);
		}

		this->changeProgramIndex(1);


		// Get number
		std::string stringNumber = "";

		while (!this->finished && this->getProgramChar() != ' ') {
			stringNumber += this->getProgramChar();
			this->changeProgramIndex(1);
		}

		int number = this->converter.string_to_int(stringNumber);
		bool result = false;


		// Compare number
		if (comparison == ">") {
			result = this->getCellValue() > number;
		}
		else if (comparison == "<") {
			result = this->getCellValue() < number;
		}
		else if (comparison == ">=") {
			result = this->getCellValue() >= number;
		}
		else if (comparison == "<=") {
			result = this->getCellValue() <= number;
		}
		else if (comparison == "=") {
			result = this->getCellValue() == number;
		}
		else if (comparison == "!=") {
			result = this->getCellValue() != number;
		}
		else {
			this->raiseError(1, "Invalid comparison");
		}

		return result;
	}


	void Interpreter::createJump() {
		this->changeProgramIndex(1);

		std::string name = "";

		while (!this->finished && this->getProgramChar() != '#') {
			name += this->getProgramChar();
			this->changeProgramIndex(1);
		}

		this->changeProgramIndex(1);
		this->jumps.append(Jump(name.data(), this->programIndex));
	}

	void Interpreter::gotoJump() {
		this->changeProgramIndex(1);

		std::string stringName = "";
		
		while (!this->finished && this->getProgramChar() != '@') {
			stringName += this->getProgramChar();
			this->changeProgramIndex(1);
		}

		this->changeProgramIndex(1);

		const char* name = stringName.data();
		unsigned int jumpLength = this->jumps.length();

		for (unsigned int i = 0; i < jumpLength; i++) {
			if (this->jumps.get(i).name == name) {
				this->programIndex = this->jumps.get(i).index;
				name = "";
				break;
			}
		}

		if (name != "") {
			this->raiseError(1, "Unknown jump");
		}
	}


	// Run the program

	int Interpreter::run() {
		while (this->errorCode == 0) {
			char command = this->getProgramChar();
			if (this->finished) break;


			switch (command) {

				// Skip whitespace
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					this->changeProgramIndex(1);
					break;


				// Skip comments
				case '/':
					while (!this->finished && this->getProgramChar() != '\n') {
						this->changeProgramIndex(1);
					}

					this->changeProgramIndex(1);
					break;

				case '\"':
					this->changeProgramIndex(1);

					while (!this->finished && this->getProgramChar() != '\"') {
						this->changeProgramIndex(1);
					}

					if (this->finished) {
						this->raiseError(1, "Missing matching \"");
					}

					else this->changeProgramIndex(1);
					break;


				// Debug strings
				case '{':
					this->changeProgramIndex(1);

					// Double {{ adds a new line
					if (this->getProgramChar() == '{') {
						std::cout << "\n";
						this->changeProgramIndex(1);
					}

					while (!this->finished && this->getProgramChar() != '}') {
						std::cout << this->getProgramChar();
						this->changeProgramIndex(1);
					}

					if (!this->finished) {
						this->changeProgramIndex(1);

						// Double }} adds a new line
						if (this->getProgramChar() == '}') {
							std::cout << "\n";
							this->changeProgramIndex(1);
						}
					}

					else this->raiseError(1, "Missing matching }");
					break;


				// Change the memory pointer
				case '>':
					this->changeCellPointer(1);
					this->changeProgramIndex(1);
					break;

				case '<':
					this->changeCellPointer(-1);
					this->changeProgramIndex(1);
					break;


				// Changing the current cell value
				case '+':
					this->changeCellValue(1);
					this->changeProgramIndex(1);
					break;

				case '-':
					this->changeCellValue(-1);
					this->changeProgramIndex(1);
					break;


				// Input / Output
				case '.':
					std::cout << this->getCellValue();
					this->changeProgramIndex(1);
					break;

				case ':':
					std::cout << (char)this->getCellValue();
					this->changeProgramIndex(1);
					break;

				case '=':
					std::cout << "\n";
					this->changeProgramIndex(1);
					break;

				case ',':
					std::cout << "\n[Interpreter]: Input is still in development\n";
					this->changeProgramIndex(1);
					break;


				// Create / goto jumps
				case '#':
					this->createJump();
					break;

				case '@':
					this->gotoJump();
					break;


				// Square brackets (loops)
				case '[':
					if (this->getCellValue() != 0) {
						this->changeProgramIndex(1);
					}
					else {
						while (this->getProgramChar() != ']') {
							this->changeProgramIndex(1);
						}

						this->changeProgramIndex(1);
					}
					break;

				case ']':
					if (this->getCellValue() == 0) {
						this->changeProgramIndex(1);
					}
					else {
						while (this->getProgramChar() != '[') {
							this->changeProgramIndex(-1);
						}

						this->changeProgramIndex(1);
					}
					break;


				// If statements
				case '?':
					this->changeProgramIndex(1);
					
					if (this->compareValue()) {
						while (!this->finished && this->getProgramChar() != '(') {
							this->changeProgramIndex(1);
						}
					}
					else {
						while (!this->finished && this->getProgramChar() != ')') {
							this->changeProgramIndex(1);
						}

						if (this->finished) {
							this->raiseError(1, "Missing matching )");
						}
					}

					this->changeProgramIndex(1);
					break;

				case ')':
					this->changeProgramIndex(1);
					break;


				// Invalid character
				default:
					this->raiseError(1, "");
					this->errorMessage = "Invalid character (ascii " + std::to_string(command) + ")";
					break;

			}


			if (this->errorCode != 0) {
				break;
			}
		}

		return this->errorCode;
	}

}