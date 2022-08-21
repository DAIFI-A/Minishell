/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:55:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/18 10:02:22 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

void	cd_home(t_env *env)
{
	t_env	*lst;
	char	*home;

	lst = env;
	home = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "HOME"))
		{
			home = env->value;
			break ;
		}
		env = env->next;
	}
	if (!home)
		return (var.exit_status = 1, ft_putendl_fd("Home not set", 2));
	else
		chdir(home);
	update_pwd(&lst, home);
}

void	cd(t_env *env, t_lexer *arg)
{
	t_env	*lst;
	char	cwd[1024];
	char	*oldpwd;

	lst = env;
	oldpwd = getcwd(cwd, sizeof(cwd));
	if (!arg->next || ft_multiple_check(arg->next->content) == 2)
		cd_home(env);
	while (arg->next)
	{
		if (ft_multiple_check(arg->next->content) == 2)
			break ;
		if (chdir(arg->next->content))
			return (var.exit_status = 1, ft_putendl_fd("No such file or directory", 2));
		update_pwd(&lst, oldpwd);
		arg = arg->next;
	}
}

void	update_pwd(t_env **lst, char *home)
{
	char	*old_pwd;
	char	cwd[1024];
	t_env	*env;

	env = (*lst);
	old_pwd = home;
	while ((*lst))
	{
		if (!ft_strcmp((*lst)->key, "PWD"))
		{
			(*lst)->value = getcwd(cwd, sizeof(cwd));
			break ;
		}
		(*lst) = (*lst)->next;
	}
	while (env)
	{
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			env->value = old_pwd;
			break ;
		}
		env = env->next;
	}
}
