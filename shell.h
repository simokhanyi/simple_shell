#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 256
#define MAX_ARG_COUNT 10
#define MAX_ARGS 10
#define UNUSED(x) (void)(x)

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*shell_prompt*/
int main(int argc, char *argv[]);
void my_exit(void);
void my_env(char **environ);
void execute_command(char *command, char **environ);
int shell_main(void);

#endif
