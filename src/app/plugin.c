#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Pathcch.h>
#include "plugin.h"
#include <Shlwapi.h>
#include <Strsafe.h>

#pragma comment(lib, "pathcch.lib")
#pragma comment(lib, "shlwapi.lib")

void plugin_load(void)
{
    DWORD dwResult;
    TCHAR szPath[MAX_PATH];
    TCHAR szModulePath[MAX_PATH];
    TCHAR szPluginPath[MAX_PATH];
    WIN32_FIND_DATA ffd;
    HMODULE hPluginModule;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    module_t* module = NULL;
    int count = 0;
    module_t** modules;

    memset(szPath, 0, sizeof(szPath));
    modules = malloc(sizeof(module_t*)*1000);
    memset(modules, 0, sizeof(module_t*)*1000);

    dwResult = GetModuleFileName(NULL, szModulePath, MAX_PATH);
    if (ERROR_INSUFFICIENT_BUFFER == dwResult) {
        fprintf(stderr, "Error: %d\n", dwResult);
        return;
    }

    PathRemoveFileSpec(szModulePath);
    StringCchCopy(szPath, MAX_PATH, szModulePath);
    StringCchCat(szPath, MAX_PATH, TEXT("\\*.dll"));

    hFind = FindFirstFile(szPath, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        fprintf(stderr, "FindFirstFile failed\n");
        return;
    }

    do
    {
        if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {
            StringCchCopy(szPluginPath, MAX_PATH, szModulePath);
            StringCchCat(szPluginPath, MAX_PATH, "\\");
            StringCchCat(szPluginPath, MAX_PATH, ffd.cFileName);

            hPluginModule = LoadLibrary(szPluginPath);
            if (hPluginModule)
            {
                module = (module_t*) GetProcAddress(hPluginModule, "module");
                if (NULL != module)
                {
                    modules[count++] = module;
                }
                else
                {
                    fprintf(stderr, "The plugin '%s' doesn't have an entrypoiny 'GetSamplePlugin'\n", szPluginPath);
                }
            }
            else
            {
                fprintf(stderr, "Failed to load plugin '%s'\n", szPluginPath);
            }
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", modules[i]->name);
    }

    for (size_t i = 0; i < count; i++) {
        if(modules[i]->init)
        {
            modules[i]->init();
        }
    }

    for (size_t i = 0; i < count; i++)
    {
        if(modules[i]->process)
        {
            modules[i]->process();
        }
    }

    for (size_t i = 0; i < count; i++)
    {
        if(modules[i]->done)
        {
            modules[i]->done();
        }
    }
    
}
