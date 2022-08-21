/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:20 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/18 09:32:47 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

# define BUFFER_SIZE 1

char *get_next_line(int fd)
{
    char tmp[800000];
    char buff[0];
    char *line;
    int i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
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
    i = 0;
    while (tmp[i])
    {
        line[i] = tmp[i];
        i++;
    }
    line[i + 1] = '\0';
    return (line);
}