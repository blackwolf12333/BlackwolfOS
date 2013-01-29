#include "arrays.h"

int indexOf(char[] array, char c) {
	int i;
	for(i = 0; i < sizeof(array); i++) {
		if(array[i] == c) {
			return i;
		} else {
			continue;
		}
	}
	return -1; // not in the array
}
