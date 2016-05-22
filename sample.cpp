#include "stdio.h"


int* getArray() {
	int array[2] = {1,2};
	return array;	
}

int main() {
	int array[2];
	array = getArray();
}