#ifndef DATA_H
#define DATA_H

#include <trog.h>
#include <trog/linalg.h>

void tr_getTimeStr(char *dest, size_t capacity);

// Given a file path, create all constituent directories if missing
void tr_createPathDirs(tr_alloc *alloc, const char *dest);

void tr_getFilePath(char *dest, const char *title);

void tr_toFile(tr_alloc *alloc, char *fileName, char *path, tr_vecd *x,
               tr_vecd **ys, size_t nvecs, char *xLabel, char **labels);

#endif // DATA_H
