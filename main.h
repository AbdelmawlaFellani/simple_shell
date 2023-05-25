#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;
char **_splitstr(char *str, char delim[]);
char *_getcmd(char *cmd);
void _cmdcheck(char *command);
char *_getenv(const char *name);

#endif
