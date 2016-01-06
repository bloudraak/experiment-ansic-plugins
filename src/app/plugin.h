#ifndef __SAMPLE_PLUGIN_H__
#define __SAMPLE_PLUGIN_H__

typedef struct module module_t;

typedef int (*module_init)();
typedef int (*module_process)();
typedef int (*module_done)();

struct module
{
    int version;
    char* name;
    module_init init;
    module_process process;
    module_done done;
};

#endif
