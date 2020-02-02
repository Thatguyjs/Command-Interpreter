#pragma once

#include <fstream>
#include <string>


class File {
public:
	File();
	File(const char* filepath);

	void load(const char* filepath);

	// Read a file
	std::string read();

	// Overwrite a file
	void write(const char* data);
	void write(std::string data);

	// Append to a file
	void append(const char* data);
	void append(std::string data);

	// Get path / data
	const char* path();
	std::string data();

	// Error code
	int error = 0;
private:
	const char* _path;
	std::string _data;
};