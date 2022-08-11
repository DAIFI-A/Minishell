/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/11 13:46:43 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini.h"

void	echo(t_lexer *arg)
{
	char	*output;
	char	*str;
	char	**s;
	int		i;

	i = 1;
	if (!arg->next)
	{
		printf("\n");
		return ;
	}
	while (arg->next)
	{
		str = ft_strdup(arg->content);
		output = ft_strjoin(output, " ");
		output = ft_strjoin(output, arg->next->content);
		arg = arg->next;
	}
	s = ft_split(output, ' ');
	if (s[1][0] == '-' && s[1][1] == 'n')
	{
		i = 2;
		while (s[i])
		{
			printf("%s ", s[i]);
			i++;
		}
	}
	else
	{
		str = ft_strdup(s[1]);
		while (s[++i])
		{
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, s[i]);
 		}
		printf("%s\n", str);
	}
	free(str);
}