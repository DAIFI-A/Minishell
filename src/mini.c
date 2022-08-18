/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:49:53 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/17 20:49:56 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_sighandler(int sig)
{
	if (sig == SIGINT && var.id == 1)
	{
		var.id = 0;
		return (kill(var.cpid, SIGKILL), (void)sig);
	}
	else if (sig == SIGINT && ft_strcmp(var.usr, "./minishell") == 0)
		return;
	else if (sig == 2 && var.id == 0)
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
		free((*head)->key);
		tmp = (*head)->next;
		free((*head));
		(*head) = tmp;
	}
}

void	ft_handle(t_env *env)
{
	char	*rtn;
	char	*stock;
	t_lexer *lexer;
	t_fds	fd;

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
		var.usr = ft_strdup(rtn);
		add_history(rtn);
		ft_parser(&lexer, rtn, &stock);
		ft_expand(&lexer, env);
		check_cmd(&env, lexer, &fd);
		if (lexer != NULL)
			ft_free_lst(&lexer);
		free(rtn);
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*env;

	var.usr = "yo";
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
