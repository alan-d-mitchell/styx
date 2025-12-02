#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <getopt.h>

#include "ops.h"

void print_styx_usage() 
{
    char* message = "sytx: a git implementation project\n\n"
                    "usage: styx <command> [option(s)]\n\n"
                    "commands: \n\tmkrepo \t\tinitalize a styx repository\n\n"
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
                fprintf(stderr, "error: unknown option\n");
                fprintf(stderr, "try: styx mkrepo --help for a list of options\n");
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

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_styx_usage();
        exit(0);
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
                fprintf(stderr, "error: unknown command\n");
                fprintf(stderr, "try: styx --help for a list of commands\n");
                break;
            default:
                break;
        }
    }

    if (argv[1][0] != '-') {
        char* command = argv[1];
        if (strcmp(command, "mkrepo") == 0) {
            parse_mkrepo_args(argc, argv, 2);
            return 0;
        } else {
            fprintf(stderr, "error: unknown command '%s'\n", command);
            print_styx_usage();

            return 1;
        }
    }
    print_styx_usage();

    return 0;
}

