#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>
#include <string.h>

#include "ops.h"

void print_mkrepo_usage()
{
    char* message = "styx mkrepo: initialize a styx repository\n\n"
                    "usage: styx mkrepo [option(s)]\n\n"
                    "options: \n\t[-h][--help] \tprint this help message and exit\n"
                            "\t[-p][--path] \tinitialize a repository at the given path\n"
                            "\t[-b][--branch] \tspecify the name of the initial branch\n\n";

    printf("%s\n", message);
}

int mkrepo(const char* path, const char* branch) {
    /* makes the .styx/ dir
        adds commits/ dir to it
        adds branches/ dir to it
        
        adds commits.txt file to commits/
        adds branches.txt file to branches/

        final structure (for now) should look like:
           ├── .styx
           ├── branches
           │   └── branches.txt
           └── commits
               └── commits.txt
    */

    const char* styx = ".styx/";
    char abspath[PATH_MAX];
    char normalized[PATH_MAX];

    if (path == NULL) 
    {
        if (getcwd(normalized, sizeof(normalized)) == NULL) {
            perror("error: failed to get current directory");
            return 1;
        }
    } else {
        if (path[0] != '/')
        {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                perror("error: failed to get current directory");
                return 1;
            }
            
            snprintf(abspath, sizeof(abspath), "%s/%s", cwd, path);
        } else {
            snprintf(abspath, sizeof(abspath), "%s", path);
        }

        // normalize path
        if (realpath(abspath, normalized) == NULL) {
            perror("error: failed to resolve path");
            return 1;
        }
    }

    char fullpath[PATH_MAX];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", normalized, styx);

    if (mkdir(fullpath, 0755) != 0 && errno != EEXIST) {
        perror("error: could not create repository");
        return 1;
    }

    if (errno == EEXIST) {
        printf("styx repository reinitialized at %s\n", fullpath);
    } else {
        printf("initialized styx repository at %s\n", fullpath);
    }
    
    char dcommits[PATH_MAX];
    snprintf(dcommits, sizeof(dcommits), "%scommits", fullpath);

    if (mkdir(dcommits, 0755) != 0 && errno != EEXIST) {
        perror("error: could not create commits directory");
        return 1;
    }
    
    char dbranches[PATH_MAX];
    snprintf(dbranches, sizeof(dbranches), "%sbranches", fullpath);

    if (mkdir(dbranches, 0755) != 0 && errno != EEXIST) {
        perror("error: could not create branches directory");
        return 1;
    }

    char fcommits[PATH_MAX];
    snprintf(fcommits, sizeof(fcommits), "%s/commits.txt", dcommits);
    
    FILE* cf = fopen(fcommits, "w");
    if (cf == NULL) {
        perror("error: could not create commits.txt");
        return 1;
    }
    fclose(cf);

    char fbranches[PATH_MAX];
    snprintf(fbranches, sizeof(fbranches), "%s/branches.txt", dbranches);

    FILE* bf = fopen(fbranches, "w");
    if (bf == NULL) {
        perror("error: could not create branches.txt");
        return 1;
    }

    if (branch == NULL) {
        fprintf(bf, "master\n");
    } else {
        fprintf(bf, "%s\n", branch);
    }
    fclose(bf);

    return 0;
}

