#include "path.h"


PathData::PathData() {
	this->_name = "";
	this->_extension = "";
}

PathData::PathData(std::string filepath) {
	int index = 0;
	std::string temp = "";

	while (filepath[index] != '\0' && filepath[index] != '.') {
		temp += filepath[index];
		index++;
	}

	index++;
	this->_name = temp;
	temp = "";

	while (filepath[index] != '\0') {
		temp += filepath[index];
		index++;
	}

	this->_extension = temp;
}

PathData::PathData(std::string name, std::string extension) {
	this->_name = name;
	this->_extension = extension;
}


std::string PathData::name() {
	return this->_name;
}

std::string PathData::extension() {
	return this->_extension;
}


void PathData::setName(std::string name) {
	this->_name = name;
}

void PathData::setExtension(std::string extension) {
	this->_extension = extension;
}


std::string PathData::fullpath() {
	if (this->_extension.length() > 0) {
		std::string fullpath = this->_name;

		fullpath += ".";
		fullpath += this->_extension;

		return fullpath;
	}
	else {
		return this->_name;
	}
}