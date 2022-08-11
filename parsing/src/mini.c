/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:34:05 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/11 09:51:34 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_free_lst(t_lexer **head)
{
	t_lexer		*tmp;

	while ((*head))
	{
		free((*head)->content);
		tmp = (*head)->next;
		free((*head));
		(*head) = tmp;
	}
}

void	ft_free_lst_env(t_env **head)
{
	t_env		*tmp;

	while ((*head))
	{
		free((*head)->value);
		free((*head)->name);
		tmp = (*head)->next;
		free((*head));
		(*head) = tmp;
	}
}

void	ft_handle(t_env *env)
{
	char	*rtn;
	t_lexer	*lexer;

	while (1)
	{
		lexer = NULL;
		rtn = readline("MiniShell>$");
		if (rtn == NULL)
		{
			printf("exit\n");
			free(rtn);
			exit(0);
		}
		add_history(rtn);
		ft_parser(&lexer, rtn);
		ft_expand(&lexer, env);
		while (lexer)
		{
			printf("node == %s\n", lexer->content);
			lexer = lexer->next;
		}
		if (lexer != NULL)
			ft_free_lst(&lexer);
		free(rtn);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = NULL;
	ft_header();
	(void)ac;
	(void)av;
	signal(2, ft_sighandler);
	rl_catch_signals = 0;
	signal(3, SIG_IGN);
	env = ft_environment(envp, env);
	ft_handle(env);
	ft_free_lst_env(&env);
	return (0);
}
