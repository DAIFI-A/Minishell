/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:26:57 by med-doba          #+#    #+#             */
/*   Updated: 2021/11/26 16:59:53 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (needle[0] == '\0' || haystack == needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		x = 0;
		if (haystack[i] == needle[x])
		{
			while (i + x < len && haystack[i + x] == needle[x])
			{
				x++;
				if (!needle[x])
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}
