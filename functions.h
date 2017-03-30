#include "par.h"
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

int findFirstPath(int argc, char ** argv);
char * getAbsolutePath(char *path);
bool isDir(char *path);
bool isLegal(char * path);
void setPar(char* par,Par *x);
char * getAPath(const char *p);

#endif


