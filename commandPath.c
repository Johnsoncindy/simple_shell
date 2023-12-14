#include "shell.h"
/**
 * cmdPath - find full path of command line arguments
 * @cmd: command name of path
 * Return: full path
 */
char *cmdPath(const char *cmd)
{
	char pth[1024];
	char *foldr;
	const char *checkFoldr = getenv("PATH");
	char *dupPth = strdup(checkFoldr);
	char *dupPath_cpy;

	if (checkFoldr == NULL || checkFoldr[0] == '\0')
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
		return (NULL);
	}
	if (!dupPth)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
		return (NULL);
	}

	dupPath_cpy = strdup(dupPth);

	foldr = strtok(dupPath_cpy, ":");
	while (foldr != NULL)
	{
		snprintf(pth, sizeof(pth), "%s/%s", foldr, cmd);
		if (access(pth, X_OK) == 0)
		{
			free(dupPth);
			free(dupPath_cpy);
			return (strdup(pth));
		}

		foldr = strtok(NULL, ":");
	}

	free(dupPth);
	free(dupPath_cpy);
	return (NULL);
}
