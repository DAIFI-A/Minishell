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

void    ft_sighandler(int sig)
{
    if (sig == 2 && var.id == 0)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (sig == 2 && var.id == 1 && strncmp(var.usr, "./minishell", 11))
    {
        printf("\n");
    }
    if (sig == 3 && var.id == 1 && strncmp(var.usr, "./minishell", 11))
    {
        printf("Quit: 3");
        printf("\n");
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
		var.id = 0;
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
		var.id = 1;
		check_cmd(&env, lexer, &fd);
		if (lexer != NULL)
			ft_free_lst(&lexer);
		free(rtn);
	}
}

void    ft_init_global(void)
{
    var.exit_status = 0;
    var.id = 0;
    var.cpid = 0;
    var.usr = NULL;
}

int main(int ac, char **av, char **envp)
{
	t_env	*env;

	ft_header();
	(void)ac;
    (void)av;
    env = NULL;
    ft_header();
    ft_init_global();
    rl_catch_signals = 0;
    signal(2, ft_sighandler);
    signal(3, ft_sighandler);
    env = ft_environment(envp, env);
    ft_handle(env);
    ft_free_lst_env(&env);
    return (0);
}
