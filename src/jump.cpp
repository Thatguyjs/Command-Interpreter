#include "jump.h"


namespace Lang {

	Jump::Jump() {}

	Jump::Jump(const char* name, long int index) {
		this->name = name;
		this->index = index;
	}

}