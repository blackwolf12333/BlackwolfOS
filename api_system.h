#ifndef API_SYSTEM_H
#define API_SYSTEM_H

typedef struct {
    char *stdout;
    void (*printf)(char *format, ...);
}

#endif
