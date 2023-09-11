#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * exit_builtins - shell exit
 *
 * Return: 0 on success, 1 on error
 */

int exit_builtins(void)
{
	char input[MAX_INPUT_LENGTH];
	
	while (1)
	{
		printf("~$ ");
		fgets(input, sizeof(input), stdin);
		
		size_t input_length = strlen(input);
		
		if (input_length > 0 && input[input_length - 1] == '\n')
		{
			input[input_length - 1] = '\0';
		}

		if (strcmp(input, "exit") == 0)
		{
			printf("Exiting the shell...\n");
			break;
		}
        
    if (strncmp(input, "echo ", 5) == 0) {
            char *text = input + 5; // Extract the text after "echo "
            printf("%s\n", text);
        }
        
        // Add more command handling as needed
        
    }
    
    return 0;
