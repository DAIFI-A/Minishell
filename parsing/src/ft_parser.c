/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:06:38 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/11 19:17:27 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	*ft_parser(t_lexer **lexer, char *str)
{
	int		i;
	char	*stock;

	i = 0;
	stock = NULL;
	while (str[i])
	{
		i = ft_skip_withespace(str, i);
		if (ft_check_case(str[i]) == 0 || ft_check_case(str[i]) == 3)
		{
			if (ft_string(lexer, &stock, str, &i) == 1)
				break ;
		}
		else if (str[i] == '|')
		{
			if (ft_pipe(&stock, str, &i, lexer) == 1)
				break ;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (ft_redirection(&stock, str, &i, lexer) == 1)
				break ;
		}
		else
			i++;
	}
	return (NULL);
}

void	ft_add_node(t_lexer **lexer, char **stock, char ch)
{
	t_lexer	*node;

	node = ft_lstnew(*stock);
	node->ch = ch;
	ft_lstadd_back(lexer, node);
	free(*stock);
	*stock = NULL;
}

char	*ft_scan_quotes(char *str, char c, int *i, int *j)
{
	char	*rtn;
	char	*tmp;
	char	*tmp1;

	rtn = ft_strdup("");
	(*i)++;
	(*j)++;
	while (1)
	{
		if (str[*i] == c)
		{
			(*i)++;
			(*j)++;
			if (str[*i] && (str[*i] == '"' || str[*i] == '\'' ))
			{
				if (str[*i] == '"')
				{
					tmp1 = ft_scan_quotes(str, '"', i, j);
					rtn = ft_strjoin(rtn, tmp1);
					free(tmp1);
				}
				else if (str[*i] == '\'')
				{
					tmp1 = ft_scan_quotes(str, '\'', i, j);
					rtn = ft_strjoin(rtn, tmp1);
					free(tmp1);
				}
			}
			if (str[*i] == ' ' || str[*i] == '\t')
				break ;
			if (str[*i] && (str[*i] == '|' || str[*i] == '>' || str[*i] == '<'))
				break ;
		}
		if (str[*i] == '\0' && (*j % 2) != 0)
			return (free(rtn),ft_putendl_fd("Error: quote >...", 2), NULL);
		else if (str[*i] == '\0' && (*j % 2) == 0)
			return (rtn);
		if ((str[*i] == ' ' || str[*i] == '\t') && (*j % 2) == 0)
			break ;
		tmp = ft_char_to_str(str[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		(*i)++;
	}
	return (rtn);
}

char	*ft_scan_pipe(char *str, char c, int *i)
{
	char	*rtn;
	char	*tmp;

	if (ft_utils_pipe(str) == 0)
	{
		rtn = ft_strdup("");
		if (str[(*i) + 1] == c)
		{
			ft_putendl_fd("Error: syntax `|'", 2);
			return (free(rtn), NULL);
		}
		tmp = ft_char_to_str(str[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		(*i)++;
		if (str[*i] == ' ' || str[*i] == '\t')
		{
			(*i) = ft_skip_withespace(str, *i);
			if (str[*i] == '|')
				return (ft_putendl_fd("Error: syntax `|'", 2), free(rtn), NULL);
		}
		return (rtn);
	}
	return (NULL);
}

char	*ft_scan_redirection(char *str, int *i, char c)
{
	char	*rtn;
	char	*tmp;
	int		count;

	count = 0;
	rtn = ft_strdup("");
	while (str[*i] == c)
	{
		if (count == 2 || str[*i] == '\0' || str[*i + 1] == '\0')
			return (free(rtn), printf("error_redirection\n"), NULL);
		tmp = ft_char_to_str(str[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		(*i)++;
		if (str[*i] == ' ' || str[*i] == '\t')
		{
			(*i) = ft_skip_withespace(str, *i);
			if (str[*i] == '<' || str[*i] == '>')
				return (free(rtn),
					ft_putendl_fd("Error: parse error (< | >)", 2), NULL);
		}
		count++;
	}
	return (rtn);
}
