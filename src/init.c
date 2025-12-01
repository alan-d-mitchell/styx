#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "ops.h"

void print_init_usage()
{
    char* message = "styx init: initialize a styx repository\n\n"
                    "usage: styx init [option(s)]\n\n"
                    "options: \n\t[-h][--help] \tprint this help message and exit\n"
                            "\t[-p][--path] \tUNIMPLEMENTED: initialize a repository at the given path\n";

    printf("%s\n", message);
}

int init() 
{
    const char* name = ".styx/";
    char* cwd = getcwd(NULL, 0);
    
    
    if (cwd == NULL) {
        perror("error: failed to get current directory");
        exit(1);
    }

    if (mkdir(name, 0755) == 0) {
        printf("styx repository initialized at: %s\n", cwd);
        exit(0);
    } else {
        if (errno == EEXIST) {
            fprintf(stderr, "error: a repository already exists at %s/%s\n", cwd, name);
            exit(1);
        } else {
            fprintf(stderr, "error: could not create repository");
            exit(1);
        }
    }

    // TODO:
    //      make the .styx/ directory which signifies
    //      that this is a styx repo so that other
    //      commands can work
    //
    //      also if commands passed (add, commit) and 
    //      no .styx/ dir present, then we error and exit

    return 0;
}

int init_at_path(const char* path) 
{
    

    return 0;
}

