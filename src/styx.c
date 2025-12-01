#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "ops.h"

void print_usage() 
{
    char* message = "sytx: a git implementation project\n\n"
                    "usage: styx <command> [option(s)]\n\n"
                    "commands: \n\tinit \t\tinitalize a styx repository\n\n"
                    "options: \n\t[-h][--help] \tprint this help message and exit\n";

    printf("%s\n", message);
}

int main(int argc, char** argv) 
{
    if (argc < 2) {
        print_usage();
        exit(1);
    }

    for (int i = 0; i < argc; i++) 
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            exit(0);
        }    
        
        if (strcmp(argv[i], "init") == 0) 
        {
            if (strcmp(argv[i + 1], "-h") == 0 || strcmp(argv[i + 1], "--help") == 0) {
                print_init_usage();
                exit(0);
            } else if (strcmp(argv[i + 1], "-p") == 0 || strcmp(argv[i + 1], "--path") == 0) {
                char* path = argv[i + 2];
                printf("PLACEHOLDER: styx repository initialized at %s\n", path);
                exit(0);
            } else {
                init();
                exit(0);
            }
        }
    }

    return 0;
}

