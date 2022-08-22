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
	int		k;

	i = 1;
	if (arg && !arg->next)
		return (ft_putendl_fd("", 1));
	str = arg->next->content;
	while (arg->next)
	{
		if (ft_multiple_check(arg->next->content) == 2)
			return ;
		output = ft_strjoin_custom(output, " ");
		output = ft_strjoin(output, arg->next->content);
		arg = arg->next;
	}
	s = ft_split(output, ' ');
	free(output);
	k = check_newline(s);
	if (k != 1)
	{
		i = k;
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

int	check_newline(char **str)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 1;
	j = 1;
	while (str[i])
	{
		if (str[i][0] == '-' && str[i][j] == 'n')
			k++;
		i++;
		j++;
	}
	return (k);
}