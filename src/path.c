/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:13 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/23 23:22:43 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

char	*get_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = ft_split(_PATH_DEFPATH, ':');
	while (paths[i])
	{
		tmp = ft_strjoin_custom(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (path == NULL)
			return (ft_free_2d(paths), free(tmp), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_2d(paths), path);
		i++;
	}
	ft_free_2d(paths);
	return (NULL);
}
