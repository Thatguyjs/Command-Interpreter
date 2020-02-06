#pragma once

#include <string>


class PathData {
public:
	PathData();
	PathData(std::string filepath);
	PathData(std::string name, std::string extension);

	std::string name();
	std::string extension();

	void setName(std::string name);
	void setExtension(std::string extension);

	std::string fullpath();

private:
	std::string _name;
	std::string _extension;
};