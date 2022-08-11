/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:08:29 by med-doba          #+#    #+#             */
/*   Updated: 2021/11/27 11:40:14 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	repetition(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != '\0' && str[i + 1] != c)
			j++;
		i++;
	}
	if (str[0] == c)
		j--;
	return (j);
}

char	*vidange(char **str, int block)
{
	while (block--)
		free(str[block]);
	return (NULL);
}

char	**how_str(char *s, char c, char **ptr)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (i > 0)
		{
			ptr[l] = (char *)malloc(sizeof(char) * (i + 1));
			if (ptr == NULL)
				vidange(ptr, l);
			ft_memcpy(ptr[l], s, i);
			ptr[l++][i] = '\0';
			s = s + i;
			i = 0;
		}
		else
			s = s + 1;
	}
	ptr[l] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;

	if (!s)
		return (NULL);
	i = repetition((char *)s, c);
	str = (char **) malloc(sizeof(char *) * (i + 1));
	if (str == NULL)
		return (NULL);
	how_str((char *)s, c, str);
	return (str);
}
