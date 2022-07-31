/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:35:27 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/31 18:41:04 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"


void	ft_lexer(char *str, t_lexer **lexer)
{
	int				i;
	char			*tmp;
	char			*stock;
	t_lexer			*node;

	i = 0;
	i = ft_skip_withespace(str, i);
	while (str[i])
	{
		if (ft_check_case(str[i]) == 0)
		{
			stock = ft_strdup("");
			while (ft_check_case(str[i]) == 0)
			{
				if ((str[i] == '"' || str[i] == '\''))
				{
					if (str[i] == '\'')
					{
						i++;
						while (str[i] && str[i] != '\'')
						{
							tmp = ft_char_to_str(str[i]);
							stock = ft_strjoin(stock, tmp);
							free(tmp);
							i++;
						}
						if (str[i] == '\0')
						{
							printf("Error quots \'\n");
							exit (1);
						}
						i++;
						break ;
					}
					else if (str[i] == '"')
					{
						i++;
						while (str[i] && str[i] != '"')
						{
							tmp = ft_char_to_str(str[i]);
							stock = ft_strjoin(stock, tmp);
							free(tmp);
							i++;
						}
						if (str[i] == '\0')
						{
							printf("Error quots '\"' \n");
							exit (1);
						}
						i++;
						break ;
					}
				}
				tmp = ft_char_to_str(str[i]);
				stock = ft_strjoin(stock, tmp);
				free(tmp);
				i++;
			}
			node = ft_lstnew(stock);
			ft_lstadd_back(lexer, node);
		}
		if(ft_check_case(str[i]) == 1)
		{
			stock = ft_strdup("");
			while (ft_check_case(str[i]) == 1)
			{
				tmp = ft_char_to_str(str[i]);
				stock = ft_strjoin(stock, tmp);
				free(tmp);
				i++;
			}
			if (ft_check_stock(stock) == 1)
				break ;
			node = ft_lstnew(stock);
			ft_lstadd_back(lexer, node);
		}
		if (ft_check_case(str[i]) == 2)
			i = ft_skip_withespace(str, i);
		if (ft_check_case(str[i]) == -1)
			break ;
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
	if (c == ' ' || c == '\t')
		return (2);
	else if (c == '\0')
		return (-1);
	else if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}
