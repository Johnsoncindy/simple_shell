#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define TOKEN_LIMIT 128
#define BUFFER_SIZE 1024

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} program_info;

extern char **environ;

ssize_t receive_input(char **lineptr, size_t *n, FILE *stream);

void string_token(char *input);

int builtIn_cmd(char **tokens);

char *cmdPath(const char *command_name);

void run_tasks(char **tokens);

int cdCmd(char **tokens);

int envCmd(void);

char *swapVariables(const char *input);

#endif
