#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <getopt.h>

#include "ops.h"

void print_styx_usage() 
{
    char* message = "sytx: a very basic implementation of git\n\n"
                    "usage: styx <command> [option(s)]\n\n"
                    "commands: \n\tmkrepo \t\tinitalize a styx repository\n"
                                "\tsee:\n\t  'styx mkrepo --help' for more info\n\n"
                    "options: \n\t[-h][--help] \tprint this help message and exit\n";

    printf("%s\n", message);
}

void parse_mkrepo_args(int argc, char** argv, int opts) 
{
    char* path = NULL;
    char* branch = NULL;

    optind = opts;

    static struct option _mkrepo[] = {
        {"help", no_argument, 0, 'h'},
        {"path", required_argument, 0, 'p'},
        {"branch", required_argument, 0, 'b'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "hp:b:", _mkrepo, NULL)) != -1) 
    {
        switch (opt) {
            case 'h':
                print_mkrepo_usage();
                exit(0);
            case 'p':
                path = optarg;
                break;
            case 'b':
                branch = optarg;
                break;
            case '?':
                fprintf(stderr, "\ntry: styx mkrepo --help for a list of options\n");
                exit(1);
            default:
                exit(1);
        }
    }

    mkrepo(path, branch);
}

int main(int argc, char** argv) 
{
    if (argc < 2) {
        print_styx_usage();
        exit(1);
    }

    // check for commands first
    // if the first arg doesnt start with a '-', it should be a command
    if (argv[1][0] != '-') {
        char* command = argv[1];
        
        // pass args to parse_mkrepo
        // pass 2 as offset because argv[0] = styx
        // argv[1] = mkrepo so other args start at argv[2]
        if (strcmp(command, "mkrepo") == 0) {
            parse_mkrepo_args(argc, argv, 2);
            return 0;
        } else {
            fprintf(stderr, "error: unknown command '%s'\n\n", command);
            fprintf(stderr, "try: styx --help for a list of commands\n");

            return 1;
        }
    }

    static struct option styx[] = {
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "h", styx, NULL)) != -1) 
    {
        switch (opt) {
            case 'h':
                print_styx_usage();
                exit(0);
            case '?':
                fprintf(stderr, "error: unknown command '%s'\n\n", argv[1]);
                fprintf(stderr, "try: styx --help for a list of commands\n");
                break;
            default:
                break;
        }
    }
    print_styx_usage();

    return 0;
}

