#include "char.h"


int CharConvert::strlen(const char* string) {
	int size = 0;

	while (string[size] != '\0') size++;

	return size;
}


long int CharConvert::pow(int number, int power) {
	int original = number;

	for (int i = 1; i < power; i++) {
		number *= original;
	}

	return power > 0 ? number : 1;
}


long int CharConvert::string_to_int(const char* string) {
	return this->_string_to_int(string);
}

long int CharConvert::string_to_int(std::string string) {
	return this->_string_to_int(string.data());
}


long int CharConvert::_string_to_int(const char* string) {
	int length = this->strlen(string);

	int result = 0;
	bool negative = false;

	for (int c = 0; c < length; c++) {
		if (c == 0 && string[0] == '-') {
			negative = true;
			continue;
		}

		if (string[c] < 48 || string[c] > 57) {
			result = 0;
			break;
		}

		int equation = (string[c] - 48) * this->pow(10, (length - c) - 1);
		result += negative ? -equation : equation;
	}

	return result;
}