#include <stdio.h>

char memory[30000] = { 0 };
unsigned int pointer = 0;


void moveLeft() {
	pointer--;
}

void moveRight() {
	pointer++;
}

void add() {
	memory[pointer]++;
}

void subtract() {
	memory[pointer]--;
}

void printValue() {
	printf("%d", memory[pointer]);
}

void printChar() {
	printf("%c", (char)memory[pointer]);
}

void printLine() {
	printf("\n");
}

void debugString(const char* string) {
	printf(string);
}


