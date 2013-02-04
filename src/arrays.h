#ifndef ARRAYS_H
#define ARRAYS_H

typedef struct array {
    char array[];
    int length;
    int (*indexOf)(char c);
}

int indexOf(char array[], char c);
int arrayLength(char array[]);

#endif
