#include "shell.h"

/**
 * builtIn_cmd - built-in commands
 * @tokens: Tokenized commands
 * Return: 1 on success, 0 otherwise
 */
int builtIn_cmd(char **tokens);
int builtIn_cmd(char **tokens)
{
	int i;
	char *lastPtr;

	if (cdCmd(tokens))
	{
		return (1);
	}
	else if (strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1] != NULL)
		{
			long status = strtol(tokens[1], &lastPtr, 10);

			if (*lastPtr != '\0')
			{
				fprintf(stderr, "Usage: exit status\n");
			}
			else
			{
				exit((int)status);
			}
		}
		return (1);
	}
	else if (strcmp(tokens[0], "echo") == 0)
	{
		/*Handle echo command*/
		for (i = 1; tokens[i] != NULL; i++)
		{
			write(1, tokens[i], strlen(tokens[i]));
			if (tokens[i + 1] != NULL)
			{
				write(1, " ", 1);
			}
		}
		write(1, "\n", 1);
		return (1);
	}
	else if (strcmp(tokens[0], "setenv") == 0)
	{
		/* Handle setenv command*/
		if (tokens[1] == NULL || tokens[2] == NULL)
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (1);
		}
		else
		{
			if (setenv(tokens[1], tokens[2], 1) != 0)
			{
				perror("setenv");
				return (1);
			}
		}
		return (1);
	}
	else if (strcmp(tokens[0], "unsetenv") == 0)
	{
		/*Handle unsetenv command*/
		if (tokens[1] == NULL)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (1);
		}
		else
		{
			if (unsetenv(tokens[1]) != 0)
			{
				perror("unsetenv");
				return (1);
			}
		}
		return (1);
	}
	else if (strcmp(tokens[0], "env") == 0)
	{
		/* Handle env command*/
		return (envCmd());
	}

	return (0);
}

/**
 * cdCmd - cd and cd - commands
 * @tokens: Tokenized commands
 * Return: 1 on success, 0 otherwise
 */
int cdCmd(char **tokens)
{

	int stdout_printed = 0;

	if (strcmp(tokens[0], "cd") == 0)
	{
		char *oldpwd = getcwd(NULL, 0);
		char *newdir = tokens[1] == NULL ||
			strcmp(tokens[1], "~") == 0
			? getenv("HOME")
			: tokens[1];

		if (newdir == NULL)
		{
			if (!stdout_printed)
			{
				write(1, oldpwd, strlen(oldpwd));
				stdout_printed = 0;
			}
			free(oldpwd);
			return (0);
		}

		if (strcmp(newdir, "-") == 0)
		{
			newdir = getenv("OLDPWD");
			if (newdir == NULL)
			{
				if (!stdout_printed)
				{
					printf("%s\n", oldpwd);
					stdout_printed = 1;
				}
				free(oldpwd);
				return (1);
			}
		}

		if (chdir(newdir) != 0)
		{
			fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", newdir);
			free(oldpwd);
			return (1);
		}

		if (strcmp(newdir, getenv("OLDPWD")) != 0)
		{
			setenv("OLDPWD", oldpwd, 1);
		}

		free(oldpwd);
		return (1);
	}

	return (0);
}

/**
 * envCmd - env command
 * Return: 1 on success, 0 otherwise
 */
int envCmd(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(1, environ[i], strlen(environ[i]));
		write(1, "\n", 1);
	}

	return (1);
}
