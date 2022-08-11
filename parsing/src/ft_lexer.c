/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:35:27 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/11 09:51:18 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_skip_withespace(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	ft_utils_pipe(char *str)
{
	int	i;

	i = 0;
	i = ft_skip_withespace(str, i);
	if (str[i] == '|')
	{
		ft_putendl_fd("Error: syntax `|'", 2);
		return (1);
	}
	i = ft_strlen(str);
	i--;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '|')
	{
		ft_putendl_fd("Error: > ...", 2);
		return (1);
	}
	return (0);
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

int	ft_find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}
