#include <stdio.h>
#include <windows.h>
#include "dbg.h"

typedef int (*lib_function) (const char *data);

int main(int argc, char *argv[]) {
    int rc = 0;
    check(argc == 4, "USAGE: ex29 libex29.so function data");

    char *lib_file = argv[1];
    char *func_to_run = argv[2];
    char *data = argv[3];

    HMODULE lib = LoadLibrary(lib_file);
    check(lib != NULL,
        "Failed to open the library %s: %lu", lib_file, GetLastError());

    lib_function func = (lib_function)GetProcAddress(lib, func_to_run);
    check(func != NULL, 
        "Did not fine %s function in the library %s: %lu", func_to_run, lib_file, GetLastError());

    rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

    rc = FreeLibrary(lib);
    check(rc != 0, "Failed to close %s: %lu", lib_file, GetLastError());

    return 0;

error:
    if (lib) FreeLibrary(lib);
    return 1;
}