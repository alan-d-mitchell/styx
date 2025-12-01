#ifndef OPS
#define OPS

#include <stdio.h>

int init();
int init_at_path(const char* path);
void print_init_usage();

int add(FILE* file, char** flags);

#endif
