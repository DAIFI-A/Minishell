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
		return (g_exit_code = 1, ft_putendl_fd("Home not set", 2));
	else
		chdir(home);
	update_pwd(&lst, home);
}

void	cd(t_env *env, t_lexer *arg)
{
	t_env	*lst;
	t_env	*node;
	int		flag;

	lst = env;
	flag = 0;
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
			flag += 1;
		env = env->next;
	}
	env = lst;
	if (flag == 0)
	{
		node = ft_lstnew_env("PWD", getcwd(NULL, 0));
		ft_lstadd_back_env(&env, node);
	}
	if (!arg->next || arg->next->content[0] == '>' || arg->next->content[0] == '<')
		cd_home(env);
	while (arg->next)
	{
		if (arg->next->content[0] == '>' || arg->next->content[0] == '|'
		|| arg->next->content[0] == '<')
			break ;
		if (chdir(arg->next->content))
			return (ft_putendl_fd("Error: No such file or directory", 2), g_exit_code = 1, (void)arg);
		update_pwd(&lst, "");
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
			old_pwd = (*lst)->value;
			(*lst)->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
			break ;
		}
		(*lst) = (*lst)->next;
	}
	(*lst) = env;
	while ((*lst))
	{
		if (!ft_strcmp((*lst)->key, "OLDPWD"))
		{
			(*lst)->value = old_pwd;
			break ;
		}
		(*lst) = (*lst)->next;
	}
}