#include"minishell.h"

int main(int argc, char const *argv[], char *envp[])
{
	char	*buffer;
	size_t	buff_size;
	char	**cmd;
	pid_t pid;

	buff_size = 1024;
	pid = fork();
	buffer = (char *)ft_calloc(sizeof(char), buff_size);
	if (!buffer)
		return (0);
	write(1, "$> ", 3);
	if (pid == 0)
	{
		while (getline(&buffer, &buff_size, stdin) > 0)
		{
			cmd = ft_split(buffer, ' ');
			cmd = ft_split(buffer, '\n');
			execve(get_path(envp, cmd[0]), cmd, envp);
		}
	}
	else
	{
		wait(NULL);
		kill(pid, SIGTERM);
	}
	free(buffer);
	return 0;
}
