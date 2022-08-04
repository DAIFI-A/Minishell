/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:00:32 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/03 17:01:14 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_env(t_env **env, t_args *arg, char **str)
{
	// export a=b then a=k => env = a=k
	//export a=b then export a+=abe => output : a=babe
	int		i;
	t_env	*lst;
	char	*value;
	char	*key;
	int		j;

	i = 1;
	j = 0;
	lst = (*env);
	if (str[i] == NULL)
	{
		while ((*env))
		{
			if ((*env)->key && (*env)->value)
				printf("declare -x %s=\"%s\"\n", (*env)->key, (*env)->value);
			(*env) = (*env)->next;
		}
	} 
	while (str[i])
	{
		while ((*env) && str[i])
		{
			if ((*env)->key)
			{
				key = ft_strdup(str[i]);
				key = ft_strrchr(key, '=');
				puts(key);
				if (!key || !ft_isalpha(key[j]) && ft_strncmp(key, "_", 1) != 0)
				{
					printf("export: `%s': not a valid identifier\n", key);
					break ;
				}
				if (!ft_strncmp(key, (*env)->key, ft_strlen((*env)->key)))
				{
					(*env)->value = ft_strdup(ft_strchr(str[i], '=') + 1); 
					break ;
				}
			}
			(*env) = (*env)->next;
		}
		if ((*env) == NULL)
		{
			(*env) = lst;
			key = ft_strdup(str[i]);
			key = get_keys(key, '=');
			value = ft_strdup(str[i]);
			value = ft_strchr(value, '=') + 1;
			lst = ft_lst_new1(key, value);
			ft_lstadd_back_prime(env, lst);
		}
		i++;
	}
}