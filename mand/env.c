/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:04:11 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/04 01:42:55 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_env	*create_env(char **envp)
{
	t_env	*lst;
	char	*value;
	char	*key;
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		value = ft_strdup(envp[i]);
		value = ft_strchr(value, '=') + 1;
		key = ft_strdup(envp[i]);
		key = get_keys(key, '=');
		if (value && key)
			lst = ft_lst_new1(key, value);
		ft_lstadd_back_prime(&env, lst);
		i++;
	}
	return (env);
}

t_env	*env_i(t_env *env)
{
	char	*value;
	char	*key;
	t_env	*lst;
	char	cwd[1024];

	value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	key = ft_strdup("PATH");
	env = ft_lst_new1(key, value);
	key = ft_strdup("PWD");
	value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	lst = ft_lst_new1(key, value);
	ft_lstadd_back_prime(&env, lst);
	// key = ft_strdup("OLDPWD");
	// value = ft_strdup("\n");
	// lst = ft_lst_new1(key, value);
	// ft_lstadd_back_prime(&env, lst);
	return (env);
}

void	env_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
