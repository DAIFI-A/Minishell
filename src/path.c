/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:13 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/26 19:10:13 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

char	*get_path(char *cmd, t_env **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = -1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = search_path(env);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		tmp = ft_strjoin_custom(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (path == NULL)
			return (ft_free_2d(paths), free(tmp), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_2d(paths), path);
	}
	ft_free_2d(paths);
	return (NULL);
}

char	**search_path(t_env **env)
{
	char	**paths;

	paths = NULL;
	while ((*env))
	{
		if (!ft_strcmp((*env)->key, "PATH"))
			paths = ft_split((*env)->value, ':');
		(*env) = (*env)->next;
	}
	return (paths);
}