#include "shell.h"

/**
 * main - main function
 * @argc: num of arguments
 * @argv: command line args
 * Return: 0 on success
 */
int main(int argc, char **argv);
int main(int argc, char **argv)
{
	char *input = NULL;
	size_t length = 0;
	char *filename = NULL;
	char *changedInput;
	FILE *file = NULL;

	if (argc == 2)
	{
		filename = argv[1];
		file = fopen(filename, "r");
		if (file == NULL)
		{
			fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], filename);
			return (127);
		}
	}
	else if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	while (1)
	{
		ssize_t read = receive_input(&input, &length, file ? file : stdin);

		if (read == -1)
		{
			break;
		}
		if (input[0] == '#' || input[0] == '\0' ||
				(input[0] == ' ' && input[1] == '#'))
		{
			continue;
		}
		changedInput = swapVariables(input);
		string_token(changedInput);
		free(changedInput);
	}

	if (file)
	{
		fclose(file);
	}
	free(input);
	return (EXIT_SUCCESS);
}
