/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:01:26 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/10 14:14:16 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

void	unset_env(t_env **env, t_lexer *arg)
{
	t_env	*tmp;
	t_env	*lst;
	t_env	*env_back;
	t_lexer	*cmd;
	char	*str;

	tmp = NULL;
	str = NULL;
	cmd = arg;
	while (cmd->next)
	{
		str = cmd->next->content;
		env_back = (*env);
		if (str[0] == '>' || str[0] == '|' || str[0] == '<')
			return ;
		if (!ft_isalpha(str[0]) && ft_strcmp(&str[0], "_"))
		{
			g_exit_code = 2;
			ft_putendl_fd("invalide inditifier", 2);
		}
		while((*env))
		{
			if ((*env)->key)
			{
				if (cmd->next && ft_strcmp((*env)->key, cmd->next->content))
				{
					lst = ft_lst_new1((*env)->key, (*env)->value);
					ft_lstadd_back_prime(&tmp, lst);
				}
			}
			(*env) = (*env)->next;
		}
		(*env) = env_back;
		while (*env)
		{
			env_back = *env;
			free((*env)->key);
			free((*env)->value);
			free(*env);
			*env = env_back->next;
		}
		cmd = cmd->next;
		*env = tmp;
	}
}