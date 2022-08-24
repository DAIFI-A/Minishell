/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:20 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/23 23:43:26 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char *get_next_line(int fd)
{
	char	tmp[800000];
	char	buff[0];
	char	*line;
	int		i;

	i = 0;
	if (fd < 0)
		return (NULL);
	tmp[0] = '\0';
	while (read(fd, buff, 1) == 1)
	{
		tmp[i] = buff[0];
		tmp[i + 1] = '\0';
		if (tmp[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	if (tmp[0] == '\0')
		return (NULL);
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memmove(line, tmp, strlen(tmp));
	line[i + 1] = '\0';
	return (line);
}