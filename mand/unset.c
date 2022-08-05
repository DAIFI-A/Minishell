/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:01:26 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/05 14:41:19 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	unset_env(t_env **env, char **str)
{
	int		i;
	int		j;
	t_env	*tmp;
	t_env	*lst;
	t_env	*env_back;

	i = 1;
	j = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[1][0] == '$' || (!ft_isalpha(str[i][j]) && ft_strncmp(str[i], "_", 1) != 0))
		{
			if (str[1][0] == '$')
				g_exit_code = 2;
			else
				g_exit_code = 1;
			ft_putendl_fd("Usage: unset [name ...]", 2);
			break ;
		}
		env_back = (*env);
		while((*env))
		{
			if ((*env)->key)
			{
				if (ft_strncmp((*env)->key, str[i], ft_strlen((*env)->key)))
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
		*env = tmp;
		tmp = NULL;
		i++;
		j++;
	}
}