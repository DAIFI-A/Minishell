/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:48:10 by med-doba          #+#    #+#             */
/*   Updated: 2021/11/27 10:56:09 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ptr;
	size_t			x;
	size_t			y;
	size_t			t;

	if (!s1 || !s2)
		return (NULL);
	y = ft_strlen(s1) + 1;
	x = ft_strlen(s2);
	t = y + x;
	ptr = malloc((y + x + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, y);
	ft_strlcat(ptr, s2, t);
	return (ptr);
}
