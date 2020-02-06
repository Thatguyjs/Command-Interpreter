#include <iostream>

#include "compiler.h"


namespace Lang {

	// Constructor
	Compiler::Compiler(const char* path) {
		bool includesFolder = false;
		std::string folder = "";

		int index = 0;

		while (path[index] != '\0') {
			if (path[index] == '/' || path[index] == '\\') {
				includesFolder = true;
			}

			folder += path[index];
			index++;
		}

		if(includesFolder) {
			int lastIndex = 0;
		
			while (index > 0) {
				if (folder[index] == '/' || folder[index] == '\\') {
					lastIndex = index;
					break;
				}

				index--;
			}

			std::string relative = "";

			for (int i = 0; i < lastIndex; i++) {
				relative += folder[i];
			}

			if (relative.length()) relative += '/';
			this->relativePath = relative;
		}
	}


	// Error handling
	void Compiler::raiseError(int code, std::string message) {
		this->errorCode = code;
		this->errorMessage = message;
	}

	std::string Compiler::lastError() {
		return this->errorMessage;
	}

	int Compiler::lastErrorCode() {
		return this->errorCode;
	}


	// Load a file
	int Compiler::load(const char* filepath) {
		this->file.load(filepath);

		if (this->file.read() == "") {
			this->raiseError(1, "Error opening file\n");
			return 1;
		}

		this->program = this->file.data();
		this->programName = this->file.path();
		this->programLength = this->program.length();

		// Headers for compilation
		this->file.load(this->relativePath + "headers.c");

		if (this->file.read() == "") {
			this->raiseError(1, "Error opening header file\n");
			return 1;
		}

		this->result = this->file.data();
		this->result += "int main() {\n";
		return 0;
	}


	// Compilation functions

	void Compiler::addDebug() {
		this->programIndex++;

		std::string result = "debugString(\"";

		if (this->program[this->programIndex] == '{') {
			result += "\\n";
			this->programIndex++;
		}

		while (!this->finished && this->program[this->programIndex] != '}') {
			result += this->program[this->programIndex];
			this->programIndex++;

			if (this->programIndex >= this->programLength) {
				this->finished = true;
			}
		}

		this->programIndex++;

		if (this->program[this->programIndex] == '}') {
			result += "\\n";
			this->programIndex++;
		}

		result += "\")";
		this->addFunction(result.data());
	}

	void Compiler::addStatement() {
		this->programIndex++;

		this->result += "\tif(memory[pointer]";

		while (!this->finished && this->program[this->programIndex+1] != '(') {
			this->result += this->program[this->programIndex];
			this->programIndex++;

			if (this->programIndex >= this->programLength) {
				this->finished = true;
			}
		}

		this->programIndex += 2;
		this->result += ") {\n";
	}

	void Compiler::addJump() {
		this->programIndex++;
		this->result += '\t';

		while (!this->finished && this->program[this->programIndex] != '#') {
			this->result += this->program[this->programIndex];
			this->programIndex++;

			if (this->programIndex >= this->programLength) {
				this->finished = true;
			}
		}

		this->programIndex++;
		this->result += ":\n";
	}

	void Compiler::gotoJump() {
		this->programIndex++;
		this->result += "\tgoto ";

		while (!this->finished && this->program[this->programIndex] != '@') {
			this->result += this->program[this->programIndex];
			this->programIndex++;

			if (this->programIndex >= this->programLength) {
				this->finished = true;
			}
		}

		this->programIndex++;
		this->result += ";\n";
	}

	void Compiler::addFunction(const char* data) {
		this->result += "\t";
		this->result += data;
		this->result += ";\n";
	}


	// Run the compiler
	int Compiler::run() {
		std::cout << "Compiling..." << std::endl;

		while (this->errorCode == 0 && !this->finished) {
			char command = this->program[this->programIndex];

			switch (command) {

				// Ignore whitespace
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					this->programIndex++;
					break;


				// Ignore comments
				case '/':
					while (!this->finished && this->program[this->programIndex] != '\n') {
						this->programIndex++;

						if(this->programIndex >= this->programLength) {
							this->finished = true;
						}
					}

					this->programIndex++;
					break;

				case '\"':
					this->programIndex++;

					while (!this->finished && this->program[this->programIndex] != '\"') {
						this->programIndex++;

						if(this->programIndex >= this->programLength) {
							this->finished = true;
						}
					}

					this->programIndex++;
					break;


				// Move memory pointer left or right
				case '>':
					this->addFunction("moveRight()");
					this->programIndex++;
					break;

				case '<':
					this->addFunction("moveLeft()");
					this->programIndex++;
					break;


				// Add or subtract from memory
				case '+':
					this->addFunction("add()");
					this->programIndex++;
					break;

				case '-':
					this->addFunction("subtract()");
					this->programIndex++;
					break;


				// Input / Output
				case '.':
					this->addFunction("printValue()");
					this->programIndex++;
					break;

				case ':':
					this->addFunction("printChar()");
					this->programIndex++;
					break;

				case '=':
					this->addFunction("printLine()");
					this->programIndex++;
					break;


				// Log to the debugger
				case '{':
					this->addDebug();
					break;


				// Square brackets
				case '[':
					this->result += "\twhile(memory[pointer] != 0) {\n";
					this->programIndex++;
					break;

				case ']':
					this->result += "\t}\n";
					this->programIndex++;
					break;


				// If statement
				case '?':
					this->addStatement();
					break;

				case ')':
					this->result += "\t}\n";
					this->programIndex++;
					break;


				// Jumps
				case '#':
					this->addJump();
					break;

				case '@':
					this->gotoJump();
					break;


				// Terminate program
				case ';':
					this->result += "\treturn 0;\n";
					this->programIndex++;
					break;

					
				// Unknown character
				default:
					this->raiseError(1, "Unknown character");
					break;

			}


			if (this->programIndex >= this->programLength) {
				this->finished = true;
			}
		}

		if (this->errorCode != 0) {
			return this->errorCode;
		}


		// Finish writing to this->result
		this->result += "\n\tgetchar();\n\treturn 0;\n}";


		// Write to a new file
		this->file.load(this->programName);

		std::string oldpath = this->file.path();
		PathData data(oldpath);

		std::string newpath = data.name();
		newpath += "_compiled";

		data.setName(newpath);

		this->file.load(data.fullpath());
		this->file.write(this->result.data());

		std::cout << data.fullpath() << std::endl;


		std::cout << "Compiled" << std::endl;
		return 0;
	}

}