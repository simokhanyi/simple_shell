#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOK_DELIM " \t\r\n\a"
#define UNUSED(x) (void)(x);

extern char **environ;

/* Function prototypes */
char *read_line(void);
char **split_line(char *line);
int execute_args(char **args);
int new_process(char **args);
void shell_interactive(void);
void shell_no_interactive(void);

/* Built-in commands */
int own_cd(char **args);
int own_env(char **args);
int own_help(char **args);
int own_exit(char **args);

#endif
