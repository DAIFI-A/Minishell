/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:06:38 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/31 18:56:06 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_parser(t_lexer *lexer, char *rtn)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (ft_locate_char(rtn, '\'') % 2 != 0 || ft_locate_char(rtn, '"') % 2 != 0)
	{
		printf("Error\n");
		exit(1);
	}
	while (tmp)
	{
		printf("parser = %s\n", tmp->content);
		tmp = tmp->next;
	}
}

int	ft_scan(char *rtn)
{
	if (ft_locate_char(rtn, '\'') % 2 != 0 || ft_locate_char(rtn, '"') % 2 != 0)
	{
		printf("Error\n");
		return (exit(1), 1);
	}
	else
		return (0);
}

int	ft_locate_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_check_stock(char *str)
{
	int	i;
	int	count1;
	int	count2;
	int count3;

	i = 0;
	count1 = 0;
	count2 = 0;
	count3 = 1;
	while (str[i])
	{
		if (str[i] == '>')
			count1++;
		if (str[i] == '<')
			count2++;
		if (str[i] == '|')
			count3++;
		i++;
	}
	if (count1 > 2 || count2 > 2 || count3 > 2)
		return (1);
	return (0);
}

// int	ft_check_pipe(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if ()
// 	}
// }
int ft_ft(char *str)
{
	int	i;
	int	j;
	int	yes;
	i = 0;
	j = 0;
	yes = 1;
	i = ft_skip_withespace(str, i);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			while (str[i] == '"')
			{
				i++;
				while (str[i] != '"')
				{
					i++;
				}
				if (str[i + 1] == '"')
					i++;

			}
			while(str[i] == '\'')
			{}
		}
		if (str[i] == '|')
		{}
		if (str[i] == '<' || str[i] == '>')
		{}
		i++;
	}
}

char	*ft_skip_quotes(t_lexer **lexer, char *str, char c, int i)
{
	char	*rtn;

	rtn = 
	while (str[i] != c)
	{
		i++;
	}
}