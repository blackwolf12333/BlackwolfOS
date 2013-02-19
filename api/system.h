#ifndef API_SYSTEM_H
#define API_SYSTEM_H

typedef struct {
    char stdout;
    void (*printf)(const char *format, ...);
}

#endif
