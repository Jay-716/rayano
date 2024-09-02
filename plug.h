#ifndef _H_PLUG
#define _H_PLUG

#include <stddef.h>

typedef struct {
    size_t plug_size;
    bool in_black;
} Plug;

typedef void (*plug_func_t)(void *);

#endif
