/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:06:38 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/01 19:13:21 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_parser(t_lexer *lexer, char *str)
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
	free(tmp);
	return (rtn);
}

char	*ft_scan_redirection(char *rtn, int *i, char c)
{
	char	*rtn;
	char	*tmp;
	int		count;

	count = 0;
	rtn = ft_strdup("");
	while (rtn[*i] == c)
	{
		if (count == 3 || rtn[*i] == '\0')
		{
			free(rtn);
			printf("error_redirection\n");
			return (NULL);
		}
		tmp = ft_char_to_str(rtn[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		(*i)++;
		count++;
	}
	return (rtn);
}

char	*ft_scan_quotes(t_lexer **lexer, char *str, char c, int *i)
{
	char	*rtn;
	char	*tmp;

	rtn = ft_strdup("");
	while (1)
	{
		if (str[*i] == c)
		{
			*i++;
			if (str[*i] && (str[*i] == '"' || str[*i] == '\'' || str[*i] != ' ' || str[*i] != '\t'))
			{
				if (str[*i] == '"')
					rtn = ft_strjoin(rtn, ft_skip_quotes(lexer, str, c, ++(*i)));
				else if (str[*i] == '\'')
					rtn = ft_strjoin(rtn, ft_skip_quotes(lexer, str, '\'', ++(*i)));
			}
			else if (str[*i] && str[*i] == ' ' || str[*i] == '\t')
				break ;
			if (str[*i] == '\0')
				return (rtn);
		}
		if (str[*i] == '\0')
		{
			free(rtn);
			return (NULL);
		}
		// if (str[*i] == ' ' || str[*i] == '\t')
		// 	break;
		tmp = ft_char_to_str(str[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		*i++;
	}
	return (rtn);
}