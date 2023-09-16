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
#define MAX_ARGS 10
extern char **environ;

/* Define the shell struct */
typedef struct {
	int argc;
	char **args;
	char **argv;
	char **env_cpy;
	int status;
	int run;
	int interactive;
	char *command;
} Shell;


/* input.h */
size_t read_command(Shell *shell);
void print_prompt();
void parse_command(Shell *sh, char *cmd);
void process_variables(Shell *shell, char **args);
/* execution.h */
void execute_command(Shell *shell);
/* utils */
void free_2d_array(char **ptr);

extern char **environ;
char **_splitstr(char *cmd);
char *_getcmd(char *cmd);
void _cmdcheck(char *command);
char *__getenv(const char *name);

/* string_fn */
int _strcmp(const char *s1, const char *s2, size_t n);
/* status_handler */
int status_handler(Shell *sh, int status);
#endif
