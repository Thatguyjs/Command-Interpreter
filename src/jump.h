#pragma once


namespace Lang {

	class Jump {
	public:
		Jump();
		Jump(const char* name, long int index);

		const char* name = "";
		long int index = -1;
	};

}