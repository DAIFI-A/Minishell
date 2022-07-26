#include "../mini.h"

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
	char	*rtn;
	t_lexer *lexer;
	int	i;

	i = 0;
	while (1)
	{
		rtn = readline("MiniShell>$");
		if (rtn == NULL)
		{
			printf("exit\n");
			free(rtn);
			exit(0);
		}
		add_history(rtn);
		lexer = ft_lstnew(rtn, 0);
		ft_lexer(rtn, lexer);
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
