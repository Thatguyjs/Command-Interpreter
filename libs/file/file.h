#pragma once

#include <fstream>
#include <string>

#include "path.h"


class File {
public:
	File();
	File(std::string filepath);

	// Setup the class data
	void load(std::string filepath);
	void load(PathData data);

	// Read a file
	std::string read();

	// Overwrite a file
	void write(const char* data);
	void write(std::string data); // TODO

	// Append to a file
	void append(const char* data); // TODO
	void append(std::string data); // TODO

	// Get path / data
	std::string path();
	std::string data();

	// Error code
	int error = 0;

private:
	std::string _path;
	std::string _data;
};