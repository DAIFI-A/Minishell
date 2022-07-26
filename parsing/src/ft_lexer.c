/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:35:27 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/26 19:03:54 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char			*ptr;
	size_t			x;
	size_t			y;
	size_t			t;

	if (!s1 || !s2)
		return (NULL);
	y = ft_strlen(s1) + 1;
	x = ft_strlen(s2);
	t = y + x;
	ptr = malloc((y + x + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, y);
	ft_strlcat(ptr, s2, t);
	free((void *)s1);
	return (ptr);
}
void	ft_lexer(char *str, t_lexer *lexer)
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
				tmp = ft_char_to_str(str[i]);
				stock = ft_strjoin_free(stock, tmp);
				free(tmp);
				i++;
			}
			node = ft_lstnew(stock, 1);
			ft_lstadd_back(&lexer, node);
			free(tmp);
			free(stock);
		}
		if(ft_check_case(str[i]) == 1)
		{
			stock = ft_strdup("");
			while (ft_check_case(str[i]) == 1)
			{
				tmp = ft_char_to_str(str[i]);
				stock = ft_strjoin(stock, tmp);
				i++;
			}
			node = ft_lstnew(stock, 1);
			ft_lstadd_back(&lexer, node);
			free(tmp);
			free(stock);
		}
		if (ft_check_case(str[i]) == 2)
			i = ft_skip_withespace(str, i);
		if (ft_check_case(str[i]) == -1)
			break ;
	}
	return ;
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
