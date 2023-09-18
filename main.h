#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMDS 10
#define MAX_ARGS 10
#define BUFFER_SIZE 2048
#define ALIASES_SIZE 100
#define SH_NAME "./hsh"

typedef unsigned int uint;
typedef struct shell shell;

struct shell
{
	int argc;
	char **argv;
	char **input;
	char **args;
	char **environ_copy;
	int num_builtins;
	int cmd_count;
	int status;
	int run;
	int interactive;
	command *builtins;
	alias aliases[ALIASES_SIZE];
};
typedef struct command
{
	char *name;
	void (*func)(shell *);
} command;
typedef struct alias
{
	char *name;
	char *value;
} alias;
extern char **environ;

/* main */
void init_shell(shell *sh, int argc, char **argv);
void free_shell(shell *sh);

/* input */
void read_input(shell *sh);
void parse_command(shell *sh, char *cmd);

/* cmd_exec */
void execute_command(shell *sh, int *curr_line);
void process_command(shell *sh);

/* cmd_find */
char *find_command(char *command);

#endif
