#pragma once

#include <string>


class CharConvert {
public:
	long int string_to_int(const char* string);
	long int string_to_int(std::string string);
	
	// static const char* int_to_string(long int number);

private:
	long int _string_to_int(const char* string);

	int strlen(const char* string);

	long int pow(int number, int power);
};