/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/17 18:06:07 by med-doba         ###   ########.fr       */
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
	if (arg && !arg->next)
		return (printf("\n"), (void)arg);
	str = arg->next->content;
	while (arg->next)
	{
		if (arg->next->content[0] == '<' || arg->next->content[0] == '>' || arg->next->content[0] == '|')
			break ;
		output = ft_strjoin_custom(output, " ");
		output = ft_strjoin_custom(output, arg->next->content);
		arg = arg->next;
	}
	s = ft_split(output, ' ');
	if (!ft_strncmp(s[1], "-n", 2))
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
		while (s[++i])
		{
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, s[i]);
 		}
		printf("%s\n", str);
	}
	ft_free_2d(s);
}