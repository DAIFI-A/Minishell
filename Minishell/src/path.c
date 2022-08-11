/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:13 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/10 21:00:53 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

char	*get_path(t_env **env, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while ((*env) && (*env)->key && ft_strcmp((*env)->key, "PATH"))
		(*env) = (*env)->next;
	paths = ft_split((*env)->value , ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}
