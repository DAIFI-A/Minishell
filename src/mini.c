#include "../mini.h"

char	*rtn;

void	ft_header(void)
{
	printf("###				 	###\n");
	printf("		minishell\n");
	printf("###		 			###\n");
}

// void	ft_handle_arg(char *rtn)
// {

// }

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_header();
	rtn = readline("prompt~");
	add_history(rtn);
	printf("%s\n", rtn);
	free(rtn);
	rtn = readline("prompt~");
	add_history(rtn);
	rl_clear_history();
	free(rtn);
	rtn = readline("prompt~");
	return (0);
}
