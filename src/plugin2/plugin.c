#include <stdio.h>
#include <stdlib.h>
#include <plugin.h>

module_t __declspec(dllexport) module =
{
    .version = 1,
    .name = "plugin2",
    .init = 0,
    .process = 0,
    .done = 0,
};
