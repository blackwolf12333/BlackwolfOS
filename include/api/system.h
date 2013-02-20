#ifndef API_SYSTEM_H
#define API_SYSTEM_H

#define NULL (void*)0

typedef struct {
    char stdout;
    void (*printf)(const char *format, ...);
} system;

#endif
