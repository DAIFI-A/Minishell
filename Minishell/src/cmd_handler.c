/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:32:48 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/13 15:51:20 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

int	check_type(char *arg)
{
	if (!ft_strcmp(arg, "pwd"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "unset"))
		return (1);
	else if (!ft_strcmp(arg, "env"))
		return (1);
	else if (!ft_strcmp(arg, "exit"))
		return (1);
	else if (!ft_strcmp(arg, "cd"))
		return (1);
	else if (!ft_strcmp(arg, "echo"))
		return (1);
	return (0);
}

void	builting(t_env **env, t_lexer *arg)
{
	if (!ft_strcmp(arg->content, "pwd"))
		pwd_env(arg);
	else if (!ft_strcmp(arg->content, "cd"))
		cd(*env, arg);
	else if (!ft_strcmp(arg->content, "unset"))
		unset_env(env, arg);
	else if (!ft_strcmp(arg->content, "echo"))
		echo(arg);
	else if (!ft_strcmp(arg->content, "export"))
		export_env(env, arg);
	else if (!ft_strcmp(arg->content, "env"))
		env_env(arg, *env);
	else if (!ft_strcmp(arg->content, "exit"))
	{
		//protect overflow;
		if (arg->next->next)
		{
			printf("too many arguments\n");
			return ;
		}
		if (!arg->next)
			exit(g_exit_code);
		else if (arg->next)
			exit(ft_atoi(arg->next->content));
	}
}

void	one_cmd(t_env **env, t_lexer *arg, char **envp, char *str)
{
	pid_t	cpid;
	char	**cmd;

	cmd  = ft_split(str, ' ');
	(void)envp;
	if (arg->content)
	{
		if (check_type(arg->content))
			builting(env, arg);
		else
		{
			cpid = fork();
			if (!cpid)
			{
				if (execve(get_path(env, arg->content), cmd, envp) == -1)
					printf("command not found\n");
			}
			waitpid(cpid, NULL, 0);
		}
	}
	return ;
}

void	check_cmd(t_env **env, t_lexer *arg, char **envp)
{
	int		i;
	t_lexer	*tmp;
	char	*str;

	i =  0;
	tmp = arg;
	str = ft_strdup(tmp->content);
	while (tmp->next)
	{
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, tmp->next->content);
		if (!ft_strcmp(tmp->content, "|"))
			i++;
		if (!ft_strcmp(tmp->content, "<") || !ft_strcmp(tmp->content, ">") || !ft_strcmp(tmp->content , ">>" ) || !ft_strcmp(tmp->content , "<<" ))
			arg->flag = 1;
		tmp = tmp->next;
	}
	if (!arg)
		return ;
	if (i == 0 && arg->flag == 1)
		content_handler(arg, *env, i);
	else if (i == 0 && arg->flag != 1)
		one_cmd(env, arg, envp, str);
	else
		content_handler(arg, *env, i);
}