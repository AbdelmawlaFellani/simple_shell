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

#define MAX_CMDS 10
#define MAX_ARGS 10
#define BUFFER_SIZE 2048
#define ALIASES_SIZE 100
#define SH_NAME "./hsh"
typedef struct shell shell;

/**
 * struct command - Struct contains builtins command name and function pointer
 * @name: Pointer to the command name string
 * @func: Pointer to the function associated with the command
 */
typedef struct
{
	char *name;
	void (*func)(shell *);
} command;

/* Define the shell struct */
struct shell
{
	int argc;
	char **argv;
	char **input;
	char **args;
	char **env_cpy;
	int num_builtins;
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
char **copy_environ(void);

/* str_utils */
unsigned int _strlen(char *s);
int _strcmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *s);
void free_2d(char ***ptr);

int is_number(char *str);
#endif
