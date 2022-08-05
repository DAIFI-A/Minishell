/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:55:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/05 15:07:39 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	cd_home(t_env *env, t_args *arg)
{
	t_env	*lst;
	char	*home;
	char	*old_pwd;
	char	*pwd;

	lst = env;
	while (env)
	{
		if(env->key)
		{
			if (!ft_strncmp(env->key, "HOME", 5))
			{
				if (chdir(env->value))
				{
					g_exit_code = 1;
					ft_putendl_fd("Home not set", 1);
					return ;
				}
				home = env->value;
				break ;
			}
		}
		env = env->next;
	}
	while (lst)
	{
		if(lst->key)
		{
			if (!ft_strncmp(lst->key, "PWD", 3))
			{
				if (lst->value)
					old_pwd = lst->value;
				lst->value = ft_strdup(home);
				break ;
			}
		}
		lst = lst->next;
	}
	lst = env;
	while (lst)
	{
		if(lst->key)
		{
			if (!ft_strncmp(lst->key, "OLDPWD", 6))
			{
				lst->value = ft_strdup(old_pwd);
				break ;
			}
		}
		lst = lst->next;
	}
}

void	cd(t_env *env, char **str, t_args *arg)
{
	char	*old_pwd;
	char	cwd[1024];
	t_env	*lst;
	int		i;

	old_pwd = NULL;
	lst = env;
	i = 1;
	if (str[i] == NULL || !ft_strncmp(str[i], "~", ft_strlen(str[i])))
		cd_home(env, arg);
	//expansion of ~!!!
	else 
	{
		while (str[i])
		{
			if (chdir(str[i]))
			{
				ft_putendl_fd("No such file or directory", 2);
				g_exit_code = 1;
				return ;
			}
			while (lst)
			{
				if (lst->key)
				{
					if (!ft_strncmp(lst->key, "PWD", 4))
					{
						if (lst->value)
							old_pwd = lst->value;
						lst->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
						break ;
					}
				}
				lst = lst->next;
			}
			lst = env;
			while (lst)
			{
				if (lst->key)
				{
					if (!ft_strncmp(lst->key, "OLDPWD", 7))
					{
						lst->value = old_pwd;
						break ;
					}
				}
				lst = lst->next;
			}
			i++;
		}
	}
}