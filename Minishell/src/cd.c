/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:55:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/09 17:19:39 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

void	cd_home(t_env *env)
{
	t_env	*lst;
	char	*home;
	char	*old_pwd;

	lst = env;
	while (env)
	{
		if(env->key)
		{
			if (!ft_strcmp(env->key, "HOME"))
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
			if (!ft_strcmp(lst->key, "PWD"))
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
			if (!ft_strcmp(lst->key, "OLDPWD"))
			{
				lst->value = ft_strdup(old_pwd);
				break ;
			}
		}
		lst = lst->next;
	}
}

void	cd(t_env *env, t_lexer *arg)
{
	char	*old_pwd;
	char	cwd[1024];
	t_env	*lst;

	old_pwd = NULL;
	lst = env;
	if (!arg->next)
		cd_home(env);
	while (arg->next)
	{
		if (chdir(arg->next->content))
		{
			puts("yo");
			ft_putendl_fd("No such file or directory", 2);
			g_exit_code = 1;
			return ;
		}
		while (lst)
		{
			if (lst->key)
			{
				if (!ft_strcmp(lst->key, "PWD"))
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
				if (!ft_strcmp(lst->key, "OLDPWD"))
				{
					lst->value = old_pwd;
					break ;
				}
			}
			lst = lst->next;
		}
		arg = arg->next;
	}
	
}