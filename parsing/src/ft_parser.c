/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:06:38 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/02 13:40:38 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_check_case_2(char c)
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

void	ft_parser(t_lexer *lexer, char *str)
{
	int		i;
	char	*stock;
	char	*tmp;
	t_lexer	*node;

	i = 0;
	i = ft_skip_withespace(str, i);
	printf("start\n");
	while (str[i])
	{
		if (ft_check_case_2(str[i]) == 0 || ft_check_case_2(str[i]) == 3)
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				stock = ft_scan_quotes(str, str[i], &i);
				if (stock == NULL)
				{
					printf("error_ft_scan_quotes\n");
					return ;
				}
				node = ft_lstnew(stock);
				ft_lstadd_back(&lexer, node);
				free(stock);
			}
			if (ft_check_case_2(str[i]) == 0)
			{
				stock = ft_strdup("");
				while (ft_check_case_2(str[i]) == 0)
				{
					tmp = ft_char_to_str(str[i]);
					stock = ft_strjoin(stock, tmp);
					free(tmp);
					i++;
				}
				node = ft_lstnew(stock);
				ft_lstadd_back(&lexer, node);
				free(stock);
			}
		}
		else if (str[i] == '|')
		{
			stock = ft_scan_pipe(str, str[i], &i);
			if (stock == NULL)
			{
				printf("error_ft_scan_quotes\n");
				return ;
			}
			node = ft_lstnew(stock);
			ft_lstadd_back(&lexer, node);
			free(stock);
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
			ft_lstadd_back(&lexer, node);
			free(stock);
		}
		else
			i++;
		i = ft_skip_withespace(str, i);
		if (str[i] == '\0')
			break ;
	}
	printf("end\n");
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

char	*ft_scan_pipe(char *str, char c, int *i)
{
	char	*rtn;
	char	*tmp;

	rtn = ft_strdup("");
	if (str[(*i) + 1] == c || str[(*i) + 1] == '\0')
	{
		printf("error_pipe\n");
		return (NULL);
	}
	tmp = ft_char_to_str(str[*i]);
	rtn = ft_strjoin(rtn, tmp);
	(*i)++;
	free(tmp);
	return (rtn);
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
			if (str[*i] == c)
			{
				free(rtn);
				printf("error_redirection_space\n");
				return (NULL);
			}
		}
		count++;
	}
	return (rtn);
}

char	*ft_scan_quotes(char *str, char c, int *i)
{
	char	*rtn;
	char	*tmp;

	rtn = ft_strdup("");
	(*i)++;
	while (1)
	{
		if (str[*i] == c)
		{
			(*i)++;
			if (str[*i] && (str[*i] == '"' || str[*i] == '\'' ) && (str[*i] != ' ' && str[*i] != '\t'))
			{
				if (str[*i] == '"')
					rtn = ft_strjoin(rtn, ft_scan_quotes(str, c, i));
				else if (str[*i] == '\'')
					rtn = ft_strjoin(rtn, ft_scan_quotes(str, '\'', i));
			}
			else if (str[*i] == ' ' || str[*i] == '\t')
				break ;
			if (str[*i] && (/*str[*i] == ' ' || str[*i] == '\t' || */str[*i] != '\'' || str[*i] != '"'))
				break ;
			if (str[*i] == '\0')
				return (rtn);
		}
		if (str[*i] == '\0')
		{
			puts("hna");
			printf("rtn == %s\n", rtn);
			free(rtn);
			return (NULL);
		}
		// if (str[*i] == ' ' || str[*i] == '\t')
		// 	break;
		tmp = ft_char_to_str(str[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		(*i)++;
	}
	return (rtn);
}