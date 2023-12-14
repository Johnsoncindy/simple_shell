#include "shell.h"
/**
 * receive_input - user input received
 * @lineptr: line pointer
 * @n: num of chars we will receive
 * @stream: receiving input stream
 * Return: characters received
 */
ssize_t receive_input(char **lineptr, size_t *n, FILE *stream)
{
	int terminalMode = isatty(fileno(stream));
	ssize_t read;

	if (terminalMode)
	{
		char *prompt = "$ ";

		write(1, prompt, strlen(prompt));
	}

	read = getline(lineptr, n, stream);

	if (!terminalMode && read == -1)
	{
		return (-1);
	}

	if (terminalMode && read > 0 && (*lineptr)[read - 1] == '\n')
	{
		(*lineptr)[read - 1] = '\0';
		read--;
	}
	return (read);
}
