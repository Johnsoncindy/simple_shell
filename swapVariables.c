#include "shell.h"

/**
 * swapVariables - swapped env var
 * @input: input str
 * Return: swapped string
 */
char *swapVariables(const char *input);
char *swapVariables(const char *input)
{
	char *swapped = NULL;
	char *start = (char *)input, *output = NULL,
	     *lastVar = NULL, *swapOutput, *envValue;
	char tmp;
	size_t valLength, outputLength, newLength, length;
	int finalExitStatus = 0;

	while (*start)
	{
		if (start[0] == '$' && start[1] != '\0')
		{
			start++;
			if (start[0] == '?')
			{
				char str_last_exit_status[16];

				sprintf(str_last_exit_status, "%d", finalExitStatus);
				envValue = str_last_exit_status;
				start++;
			}
			else if (start[0] == '$')
			{
				char str_pid[16];

				sprintf(str_pid, "%d", getpid());
				envValue = str_pid;
				start++;
			}
			else
			{
				lastVar = start;
				while (*start && (isalnum(*start) || *start == '_'))
				{
					start++;
				}
				if (start == lastVar)
				{
					free(swapOutput);
					continue;
				}

				tmp = *start;
				*start = '\0';

				envValue = getenv(lastVar);
			}

			if (envValue)
			{
				valLength = strlen(envValue);
				outputLength = output ? strlen(output) : 0;
				newLength = outputLength + valLength;

				swapOutput = (char *)malloc(newLength + 1);
				if (!swapOutput)
				{
					perror("malloc");
					free(swapped);
					return (NULL);
				}

				if (outputLength > 0)
				{
					strcpy(swapOutput, output);
				}
				else
				{
					swapOutput[0] = '\0';
				}
				strcat(swapOutput, envValue);
				free(swapped);
				swapped = swapOutput;

				*start = tmp;
			}
			else
			{
				*start = tmp;
			}
		}

		if (!swapped)
		{
			length = output ? strlen(output) : 0;
			swapOutput = (char *)malloc(length + 2);
			if (!swapOutput)
			{
				perror("malloc");
				free(swapped);
				return (NULL);
			}
			if (length > 0)
			{
				strcpy(swapOutput, output);
			}
			else
			{
				swapOutput[0] = '\0';
			}
			swapOutput[length] = *start;
			swapOutput[length + 1] = '\0';
			free(output);
			output = swapOutput;
		}

		start++;
	}

	return (swapped ? swapped : (output ? output : strdup(input)));
}
