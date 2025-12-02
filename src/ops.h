#ifndef OPS
#define OPS

#include <stdio.h>

int mkrepo(const char* path, const char* branch);
void print_mkrepo_usage();

int add(FILE* file, char** flags);

#endif
