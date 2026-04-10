#ifndef DATA_H
#define DATA_H

#include <forge.h>
#include <forge/linalg.h>

void f_getTimeStr(char *dest, size_t capacity);

// Given a file path, create all constituent directories if missing
void f_createPathDirs(f_alloc *alloc, const char *dest);

void f_getFilePath(char *dest, const char *title);

void f_toFile(f_alloc *alloc, char *fileName, char *path, f_vecd *x,
              f_vecd **ys, size_t nvecs, char *xLabel, char **labels);

#endif // DATA_H
