#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_ARGS 10
typedef struct shell shell;

/**
 * struct command - Struct contains builtins command name and function pointer
 * @name: Pointer to the command name string
 * @process: Paointer to the process function associated with the command
 */
typedef struct command
{
	char *name;
	void (*process)(shell *);
} command;

/**
 * struct shell - Struct representing the shell
 *
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * @input: Array of input lines
 * @args: Array of command arguments
 * @builtins_count: Number of built-in commands
 * @cmd_count: Number of executed commands
 * @status: Exit status of the shell
 * @run: Flag indicating if the shell is running
 * @interactive: Flag indicating if the shell is in interactive mode
 * @builtins: Array of built-in commands
 */
struct shell
{
	int argc;
	char **argv;
	char **input;
	char **args;
	int builtins_count;
	int cmd_count;
	int status;
	int run;
	int interactive;
	command *builtins;
};

extern char **environ;

/* main */
void init_shell(shell *sh, int argc, char **argv);
void free_shell(shell *sh);

/* input */
void read_input(shell *sh);
void parse_cmd(shell *sh, char *cmd);

/* cmd_exec */
void execute_cmd(shell *sh, int *curr_line);
void process_cmd(shell *sh);

/* cmd_find */
char *find_cmd(char *command);

/* builtins */
command *get_builtins(void);
void cmd_env(shell *sh);
void cmd_exit(shell *sh);

/* sys_utils */
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *_getenv(const char *name);

/* str_utils */
unsigned int _strlen(char *s);
int _strcmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *s);
void free_2d(char ***ptr);

int is_number(char *str);
#endif
