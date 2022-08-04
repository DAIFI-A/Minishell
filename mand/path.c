/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:13 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/03 17:06:18 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_path(t_env *env, t_args *arg)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while (env && env->key && ft_strncmp(env->key, "PATH", 4))
		env = env->next;
	paths = ft_split(env->value , ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, arg->cmd[0]);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	check_path(t_env *env, t_args *arg)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = env;
	while(lst)
	{
		if (!(ft_strncmp(lst->key, "PATH", 4)))
		{
			if (lst->value)
			{
				arg->paths = ft_split(lst->value, ':');
				i = 1;
			}
			break ;
		}		
		lst = lst->next;
	}
	if (i != 1)
	{
		ft_putendl_fd("PATH not found", 2);
		exit(1);
	}
}