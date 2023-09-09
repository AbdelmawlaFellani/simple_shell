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

#define MAX_COMMAND_LENGTH 100

/* Define the shell struct */
typedef struct {
	int argc;
	char **args;
	char **argv;
	char **env_cpy;
	char *input;
	int status;
	int run;
	int interactive;
	char *command;
	size_t command_size;
} Shell;


/* input.h */
ssize_t read_command(Shell *shell);
void print_prompt();

/* execution.h */
void execute_command(Shell *shell);
/* utils */
void free_string_array(char ***ptr);

extern char **environ;
char **_splitstr(char *cmd);
char *_getcmd(char *cmd);
void _cmdcheck(char *command);
char *_getenv(const char *name);

#endif
