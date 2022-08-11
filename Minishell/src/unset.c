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
	char	*str;

	tmp = NULL;
	str = NULL;
	while (arg->next)
	{
		str = arg->next->content;
		env_back = (*env);
		if ((!ft_isalpha(str[0]) && ft_strcmp(&str[0], "_") != 0))
		{
			g_exit_code = 2;
			ft_putendl_fd("Error: invalide inditifier", 2);
		}
		while((*env))
		{
			if ((*env)->key)
			{
				if (ft_strcmp((*env)->key, arg->next->content))
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
		arg = arg->next;
		*env = tmp;
		tmp = NULL;
	}
}