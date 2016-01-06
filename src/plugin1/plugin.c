#include <stdio.h>
#include <stdlib.h>
#include <plugin.h>

static int init()
{
    printf("%s: init\n", "plugin1");
    return 0;
}

module_t __declspec(dllexport) module =
{
    .version = 1,
    .name = "plugin1",
    .init = init,
    .process = 0,
    .done = 0,
};
