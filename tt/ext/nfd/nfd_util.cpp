#include <stdio.h>
#include <nfd.h>
#include "nfd_util.h"

std::string f_open_file() {
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

    std::string str;
    if ( result == NFD_OKAY ) {
        str = std::string(outPath);
        puts("Success!");
        puts(outPath);
        free(outPath);
    } else if ( result == NFD_CANCEL ) {
        puts("User pressed cancel.");
    } else {
        printf("Error: %s\n", NFD_GetError() );
    }

    return str;
}

std::string f_save_file() {
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_SaveDialog(NULL, NULL, &outPath);

    std::string str;
    if ( result == NFD_OKAY ) {
        str = std::string(outPath);
        puts("Success!");
        puts(outPath);
        free(outPath);
    } else if ( result == NFD_CANCEL ) {
        puts("User pressed cancel.");
    } else {
        printf("Error: %s\n", NFD_GetError() );
    }

    return str;
}

