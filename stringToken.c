#include "shell.h"

/**
 * string_token - tokenize input string
 * @input: input string
 */
void string_token(char *input);
void string_token(char *input)
{
	char *filterInput = input;
	char *token;
	char *delimiter = " \n;";
	char **tokens = malloc(sizeof(char *) * TOKEN_LIMIT);
	int tokenCounter = 0;
	int j;
	char *limit;

	if (!tokens)
	{
		perror("memory allocation failed");
		exit(EXIT_FAILURE);
	}
	while (*filterInput == ' ' || *filterInput == '\t')
	{
		filterInput++;
	}
	limit = filterInput + strlen(filterInput) - 1;
	while (limit > filterInput && (*limit == ' ' || *limit == '\t'))
	{
		*limit = '\0';
		limit--;
	}
	token = strtok(filterInput, delimiter);
	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
			free(token);
		}
		tokens[tokenCounter] = strdup(token);
		if (!tokens[tokenCounter])
		{
			perror("memory allocation failed");
			exit(EXIT_FAILURE);
		}
		tokenCounter++;
		token = strtok(NULL, delimiter);
	}
	tokens[tokenCounter] = NULL;

	if (tokenCounter > 0)
	{
		if (!builtIn_cmd(tokens))
		{
			run_tasks(tokens);
		}
	}

	for (j = 0; j < tokenCounter; j++)
	{
		free(tokens[j]);
	}
	free(tokens);
}
