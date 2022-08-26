/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:20 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/26 02:52:31 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_next_line(int fd)
{
	char	buff;
	char	*line;
	int		i;
	int		rd;

	i = 0;
	rd = 0;
	line = (char *)malloc(10000 * sizeof(char));
	rd = read(fd, &buff, 1);
	while (rd > 0)
	{
		line[i++] = buff;
		if (buff == '\n')
			break ;
	}
	if ((!line[i - 1] && !rd) || rd == -1)
	{
		free(line);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (line);
}
