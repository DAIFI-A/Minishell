/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 10:57:18 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/07 16:00:26 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_free_2d(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

t_env	*ft_environment(char **envp, t_env *env)
{
	t_env	*node;
	char	**ptr;
	int		i;

	i = 0;
	node = env;
	if (envp[0] == NULL)
	{
		node = ft_lstnew_env("PWD", getcwd(NULL, 0));
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("OLDPWD", "");
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("SHLVL", "1");
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("_", "/usr/bin/env");
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		ft_lstadd_back_env(&env, node);
		return (env);
	}
	while (envp[i])
	{
		ptr = ft_split(envp[i], '=');
		node = ft_lstnew_env(ptr[0], ptr[1]);
		ft_lstadd_back_env(&env, node);
		i++;
		ft_free_2d(ptr);
	}
	return (env);
}
