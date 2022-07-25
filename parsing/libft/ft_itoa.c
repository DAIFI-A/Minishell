/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 03:20:45 by med-doba          #+#    #+#             */
/*   Updated: 2021/11/27 15:00:43 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(int nbr)
{
	int	length;

	length = 0;
	if (nbr <= 0)
		length++;
	while (nbr != 0)
	{
		length++;
		nbr /= 10;
	}
	return (length);
}

int	ft_to(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		taille;

	taille = len(n);
	str = malloc(sizeof(char) * (taille + 1));
	if (str == NULL)
		return (NULL);
	str[taille] = '\0';
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		--taille;
		str[taille] = ft_to(n % 10) + 48;
		n = n / 10;
	}
	return (str);
}
