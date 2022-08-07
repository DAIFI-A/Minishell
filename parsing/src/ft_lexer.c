/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:35:27 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/07 16:56:10 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_lexer(t_lexer ** lexer)
{
	while (*(lexer))
	{
		if ()p\
	}
}
int	ft_skip_withespace(char *str, int i)
{
	while(str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

char	*ft_char_to_str(char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	ft_check_case(char c)
{
	if (c == '\0')
		return (-1);
	else if (c == '<' || c == '>' || c == '|')
		return (1);
	else if (c == ' ' || c == '\t')
		return (2);
	else if (c == '"' || c == '\'')
		return (3);
	else
		return (0);
}