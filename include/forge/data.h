#ifndef DATA_H
#define DATA_H

#include <forge.h>
#include <forge/linalg.h>

void f_getTimeStr(char *dest);

// Given a file path, create all constituent directories if missing
void f_createPathDirs(const char *dest);

void f_getFilePath(char *dest, const char *title);

void f_toCSVfile(const char *dest, const f_vecd *x, const f_vecd **ys,
                 const size_t nvecs, const char *xLabel, const char **labels);

#endif // DATA_H
