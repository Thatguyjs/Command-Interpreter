#include "file.h"


File::File() {

}

File::File(const char* filepath) {
	this->_path = filepath;
}


void File::load(const char* filepath) {
	this->_path = filepath;
	this->error = 0;
}


std::string File::read() {
	std::ifstream file(this->_path);

	if (!file.is_open()) {
		this->error = 1;
		return "";
	}

	std::string content(
		(std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>())
	);

	this->_data = content;
	return this->_data;
}


void File::write(const char* data) {

}

void File::write(std::string data) {

}


void File::append(const char* data) {

}

void File::append(std::string data) {

}


const char* File::path() {
	return this->_path;
}

std::string File::data() {
	return this->_data;
}