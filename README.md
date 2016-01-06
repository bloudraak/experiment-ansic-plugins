# ANSI C Plugin

This is a simple experiment how to write a C application that could be extended at runtime.

The project consists of an app and three plugins. Each plugin is compiled as its own DLL. When the app starts, it uses WIN32 APIs to load all the plugins. It then searches for a struct which is exported from the dll. I then calls methods in the plugin.

Much of this model came from Apache HTTP Server and NGINX.

It currently only works on Windows.  
