#include "arrays.h"

int indexOf(char array[], char c) {
	int i;
	for(i = 0; i < arrayLength(array); i++) {
		if(array[i] == c) {
			return i;
		} else {
			continue;
		}
	}
	return -1; // not in the array
}

int arrayLength(char array[]) {
	int i=0;
	while(array[i]) {
		i++;
	}
	return i;
}
