// Amaan Shah, UIC, Spring 2021
// stack.cpp

#include <cstdio>
#include <cstring>
#include <cctype>
#include "header.h"

ValueStack:: ValueStack() {
	darr = new int[2];
	size = 2;
	inUse = 0;
}

ValueStack:: ~ValueStack() {
    delete[] this->darr;
}

void ValueStack:: push(int y) {
	if (this->inUse == this->size) {
		grow();
	}
	this->darr[this->inUse] = y;
	this->inUse = this->inUse + 1;
}

void ValueStack:: grow() {
	int* temp = this->darr;
	this->darr = new int[this->size + 2];

	for (int i = 0; i < this->size; i++) {
		this->darr[i] = temp[i];
	}
	delete[] temp;

	this->size = this->size + 2;
}

void ValueStack:: pop() {
	this->inUse = this->inUse - 1;
}

int ValueStack:: top() {
	if (this->inUse == 0) {
		printf("Invalid expression.");
		return -999;
	}
	return (this->darr[this->inUse - 1]);
}

bool ValueStack:: is_empty() {
   if (this->inUse == 0) {
      return true;
   } else {
      return false;
   }
}



OperatorStack:: OperatorStack() {
	darr = new char[2];
	size = 2;
	inUse = 0;
}

OperatorStack:: ~OperatorStack() {
  delete[] this->darr;
}

void OperatorStack:: push(char y) {
	if (this->inUse == this->size) {
		grow();
	}

	this->darr[this->inUse] = y;
	this->inUse = this->inUse + 1;
}

void OperatorStack:: grow() {
	char* temp = this->darr;
	this->darr = new char[this->size + 2];

	for (int i = 0; i < this->size; i++) {
		this->darr[i] = temp[i];
	}
	delete[] temp;

	this->size = this->size + 2;
}

void OperatorStack:: pop() {
	this->inUse = this->inUse - 1;
}

char OperatorStack:: top() {
	return (this->darr[this->inUse - 1]);
}

bool OperatorStack:: is_empty() {
   if (this->inUse == 0) {
      return true;
   } else {
      return false;
   }
}