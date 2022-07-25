/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:35:27 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/25 19:00:23 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_check_case(char c)
{
	if (c == ' ' || c == '\0' || c == '|')
		return (1);
	else if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

void	ft_lexer(char *str, t_lexer *lexer)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (ft_check_case(str[i]) == 0)
			i++;
		j = i;
		lexer = ft_lstnew(str);

	}
	printf("%s\n", str);
}

char	*ft_rtn(char *str)
{
	int	i;

	i = 0;
	while ()
}

