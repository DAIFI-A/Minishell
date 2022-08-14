/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:00:32 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/12 17:17:22 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	export_env(t_env **env, t_lexer *arg)
{
	t_env	*lst;
	char	*value;
	char	*key;

	lst = (*env);
	if (arg->next == NULL || !ft_strcmp(arg->next->content, ">"))
	{
		while ((*env))
		{
			if ((*env)->key && (*env)->value)
				printf("declare -x %s=\"%s\"\n", (*env)->key, (*env)->value);
			(*env) = (*env)->next;
		}
		(*env) = lst;
		return ;
	}
	while (arg)
	{
		lst = (*env);
		while ((*env) && arg->next)
		{
			key = ft_strdup(arg->next->content);
			key = get_keys(key, '=');
			if (!key || (!ft_isalpha(key[0]) && ft_strcmp(key, "_") != 0))
			{
				g_exit_code = 1;
				printf("export: `%s': not a valid identifier\n", key);
				break ;
			}
			if (!ft_strcmp(key, (*env)->key))
			{
				(*env)->value = ft_strdup(ft_strchr(arg->next->content, '=') + 1);
				(*env) = lst;
				break ;
			}
			(*env) = (*env)->next;
		}
		if ((*env) == NULL)
		{
			(*env) = lst;
			value = ft_strdup(arg->next->content);
			value = ft_strchr(value, '=') + 1;
			key = ft_strdup(arg->next->content);
			key = get_keys(key, '=');
			lst = ft_lst_new1(key, value);
			ft_lstadd_back_prime(env, lst);
		}
		arg = arg->next;
	}
}