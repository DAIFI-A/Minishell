/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:01:26 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/03 17:02:51 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	unset_env(t_env **env, char **str)
{
	int		i;
	t_env	*tmp;
	t_env	*lst;
	t_env	*env_back;

	i = 1;
	tmp = NULL;
	while (str[i])
	{
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
	}
}