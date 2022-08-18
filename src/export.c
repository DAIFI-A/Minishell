/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:00:32 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/18 08:23:37 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	*export_env(t_env **env, t_lexer *arg)
{
	t_env	*lst;
	char	*key;

	lst = (*env);
	ft_sort_env(env);
	if (arg->next && ft_multiple_check(arg->next->content))
	{
		if (arg->next->ch == '"' || arg->next->ch == '\'')
			ft_putendl_fd("Error: not a valid identifier", 2);
		return (NULL);
	}
	if (!arg->next)
		return (ft_print_exported(env), NULL);
	while (arg)
	{
		lst = (*env);
		while ((*env) && arg->next)
		{
			key = get_keys(arg->next->content, '=');
			if (!key || (!ft_isalpha(key[0]) && ft_strcmp(key, "_")))
				return (g_exit_code = 1, ft_putendl_fd("Error: export", 2), NULL);
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
			ft_add_export(arg->next->content, env);
		}
		arg = arg->next;
	}
	return (NULL);
}

void	ft_print_exported(t_env **env)
{
	t_env	*tmp;
	t_env	*top;
	int		i;

	tmp = *env;
	top = *env;
	i = 0;
	while (tmp)
		{
			(*env) = top;
			while ((*env))
			{
				if ((*env)->key && (*env)->value && (*env)->index == i)
				{
					printf("declare -x %s=\"%s\"\n", (*env)->key, (*env)->value);
					i++;
					break;
				}
				(*env) = (*env)->next;
			}
			tmp = tmp->next;
		}
	(*env) = top;
}

int	ft_multiple_check(char *arg)
{
	if ((arg[0] == '>' || arg[0] == '|' || arg[0] == '<'))
		return (1);
	else
		return (0);
}

void	ft_sort_env(t_env **env)
{
	t_env	*top;
	t_env	*tmp;
	int		i;

	tmp = *env;
	top = *env;
	while (top)
	{
		i = 0;
		*env = tmp;
		while (*env)
		{
			if (ft_strcmp(top->key, (*env)->key) > 0)
				i++;
			*env = (*env)->next;
		}
		top->index = i;
		top = top->next;
	}
	*env = tmp;
	top = tmp;
}

void	ft_add_export(char *str, t_env **env)
{
	char	*value;
	char	*key;
	t_env	*lst;

	value = ft_strchr(str, '=') + 1;
	key = get_keys(str, '=');
	lst = ft_lst_new1(key, value);
	ft_lstadd_back_prime(env, lst);
}