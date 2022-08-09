/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:06:38 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/09 16:44:22 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_parser(t_lexer **lexer, char *str)
{
	int		i;
	int		j;
	char	ch;
	char	*stock;
	char	*tmp;
	t_lexer	*node;

	i = 0;
	j = 0;
	i = ft_skip_withespace(str, i);
	stock = NULL;
	while (str[i])
	{
		if (ft_check_case(str[i]) == 0 || ft_check_case(str[i]) == 3)
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				ch = str[i];
				if (stock == NULL)
					stock = ft_scan_quotes(str, str[i], &i, &j);
				else
				{
					tmp = ft_scan_quotes(str, str[i], &i, &j);
					stock = ft_strjoin(stock, tmp);
					free(tmp);
				}
				if (stock == NULL)
				{
					printf("error_ft_scan_quotes\n");
					return ;
				}
				node = ft_lstnew(stock);
				node->ch = ch;
				ft_lstadd_back(lexer, node);
				free(stock);
				stock = NULL;
			}
			if (ft_check_case(str[i]) == 0)
			{
				stock = ft_strdup("");
				while (ft_check_case(str[i]) == 0)
				{
					tmp = ft_char_to_str(str[i]);
					stock = ft_strjoin(stock, tmp);
					free(tmp);
					i++;
				}
				if (str[i] != '"' && str[i] != '\'')
				{
					node = ft_lstnew(stock);
					ft_lstadd_back(lexer, node);
					free(stock);
					stock = NULL;
				}
			}
		}
		else if (str[i] == '|')
		{
			stock = ft_scan_pipe(str, str[i], &i);
			if (stock == NULL)
				return ;
			node = ft_lstnew(stock);
			ft_lstadd_back(lexer, node);
			free(stock);
			stock = NULL;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			stock = ft_scan_redirection(str, &i, str[i]);
			if (stock == NULL)
			{
				printf("error_ft_scan_quotes\n");
				return ;
			}
			node = ft_lstnew(stock);
			ft_lstadd_back(lexer, node);
			free(stock);
			stock = NULL;
		}
		else
			i++;
		i = ft_skip_withespace(str, i);
		if (str[i] == '\0')
			break ;
	}
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
		{
			free(rtn);
			printf("error_redirection\n");
			return (NULL);
		}
		tmp = ft_char_to_str(str[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		(*i)++;
		if (str[*i] == ' ' || str[*i] == '\t')
		{
			(*i) = ft_skip_withespace(str, *i);
			if (str[*i] == '<' || str[*i] == '>')
			{
				free(rtn);
				printf("error_redirection_space\n");
				ft_putendl_fd("Error: parse error (< || >)", 2);
				return (NULL);
			}
		}
		count++;
	}
	return (rtn);
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
		{
			ft_putendl_fd("Error: quote >...", 2);
			free(rtn);
			return (NULL);
		}
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
