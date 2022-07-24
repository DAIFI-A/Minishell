#include "../mini.h"

char	*rtn;

void	ft_check_cmd(char *str)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = ft_split(str, ' ');
	while (ptr[i])
		printf("%s\n", ptr[i++]);
}
void	ft_sighandler(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle()
{
	while (1)
	{
		rtn = readline("minishell>");
		if (rtn == NULL)
		{
			printf("exit\n");
			free(rtn);
			exit(0);
		}
		add_history(rtn);
		ft_check_cmd(rtn);
		free(rtn);
	}
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	signal(2, ft_sighandler);
	rl_catch_signals = 0;
	signal(3, SIG_IGN);
	ft_header();
	ft_handle();
	return (0);
}
