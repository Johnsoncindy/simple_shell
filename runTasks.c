#include "shell.h"
/**
 * run_tasks - execute a command with arguments
 * @tokens: array of tokens representing the command and its arguments
 */
void run_tasks(char **tokens);
void run_tasks(char **tokens)
{
	pid_t cPid;
	int status;

	cPid = fork();
	if (cPid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (cPid == 0)
	{
		char *cmd = tokens[0];
		char *envp[] = {"TERM=xterm", NULL};

		if (strchr(cmd, '/'))
		{
			if (execve(cmd, tokens, envp) == -1)
			{
				exit(2);
			}
		}
		else
		{
			char *exec_path = cmdPath(cmd);

			if (exec_path == NULL)
			{
				exit(2);
			}

			if (execve(exec_path, tokens, envp) == -1)
			{
				exit(2);
			}
		}
	}
	else
	{
		waitpid(cPid, &status, 0);
	}
}
