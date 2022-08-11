/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:08:15 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/11 18:56:35 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_pipe(char **stock, char *str, int *i, t_lexer **lexer)
{
	*stock = ft_scan_pipe(str, str[*i], i);
	if (*stock == NULL)
		return (1);
	ft_add_node(lexer, stock, 0);
	return (0);
}

int	ft_redirection(char **stock, char *str, int *i, t_lexer **lexer)
{
	*stock = ft_scan_redirection(str, i, str[*i]);
	if (*stock == NULL)
		return (1);
	ft_add_node(lexer, stock, 0);
	return (0);
}

void	ft_else(char *str, char **stock, int *i, int *j)
{
	char *tmp;

	tmp = ft_scan_quotes(str, str[*i], i, j);
	*stock = ft_strjoin(*stock, tmp);
	free(tmp);
}

void	ft_string(t_lexer **lexer, char **stock, char *str, int *i)
{
	int		j;
	char	ch;

	j = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		ch = str[*i];
		if (stock == NULL)
			stock = ft_scan_quotes(str, str[*i], &i, &j);
		else
			ft_else(str, &stock, &i, &j);
		if (stock == NULL)
			return (NULL);
		ft_add_node(lexer, &stock, ch);
	}
	if (ft_check_case(str[*i]) == 0)
	{
		stock = ft_strdup("");
		while (ft_check_case(str[*i]) == 0)
			stock = ft_join(stock, str[(*i)++]);
		if (str[*i] != '"' && str[*i] != '\'')
			ft_add_node(lexer, &stock, ch);
	}
}