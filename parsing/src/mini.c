/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:34:05 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/15 16:22:47 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	exit_status = 0;

void	ft_sighandler(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == 3)
	{
		return ;
	}
}

int	ft_buffer(char *buff)
{
	if (buff == NULL)
		return (1);
	return (0);
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
	t_lexer	*top;
	char	*stock;

	while (1)
	{
		lexer = NULL;
		rtn = readline("MiniShell>$");
		if (rtn == NULL)
		{
			printf("exit\n");
			free(rtn);
			return ;
		}
		add_history(rtn);
		ft_parser(&lexer, rtn, &stock);
		ft_expand(&lexer, env);
		top = lexer;
		if (lexer != NULL)
		{
			if (ft_strcmp(lexer->content, "env") == 0)
				ft_env(env);
			if (ft_strcmp(lexer->content, "pwd") == 0)
				ft_pwd();
			if (ft_strcmp(lexer->content, "exit") == 0)
			{
				if (lexer->next == NULL)
				{
					printf("Exit\n");
					exit(exit_status);
				}
				else
					ft_exit(lexer->next->content);
			}
			if (ft_strcmp(lexer->content, "export") == 0)
			{
				if (!lexer->next)
					ft_export(&env, NULL);
				else
					ft_export(&env, lexer->next->content);
			}
			lexer = lexer->next;
		}
		lexer = top;
		// while (lexer)
		// {
		// 	printf("%s\n", lexer->content);
		// 	// printf("%s\n", lexer->next->content);
		// 	lexer = lexer->next;
		// }
		}
		if (lexer != NULL)
			ft_free_lst(&lexer);
		free(rtn);
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
	signal(3, ft_sighandler);
	env = ft_environment(envp, env);
	ft_handle(env);
	ft_free_lst_env(&env);
	return (0);
}