/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:31:15 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/08 11:20:05 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_expand(t_lexer **lexer, t_env *env)
{
	char	*tmp;
	t_lexer		*head;

	head = (*lexer);
	while ((*lexer))
	{
		if ((*lexer)->ch == '"')
		{
			tmp = ft_parse_expand((*lexer)->content, env);
			(*lexer)->content = ft_strdup(tmp);
			free(tmp);
		}
		(*lexer) = (*lexer)->next;
	}
	(*lexer) = head;
}

char	*ft_parse_expand(char *str, t_env *env)
{
	char	*rtn;
	char	*tmp1;
	char	*tmp2;
	char	*stock;
	int		i;
	t_env	*head;

	i = 0;
	rtn = ft_strdup("");
	stock = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9'))
			{
				tmp2 = ft_char_to_str(str[i]);
				stock = ft_strjoin(stock, tmp2);
				free(tmp2);
				i++;
			}
			if (stock)
			{
				head = env;
				while (env)
				{
					if (ft_strcmp(env->name, stock) == 0)
					{
						free(stock);
						stock = ft_strdup(env->value);
						rtn = ft_strjoin(rtn, stock);
						break;
					}
					env = env->next;
				}
				free(stock);
				stock = ft_strdup("");
				env = head;
			}
		}
		if (str[i] == '\0')
			break ;
		if (str[i] != '$')
		{
			tmp1 = ft_char_to_str(str[i]);
			rtn = ft_strjoin(rtn, tmp1);
			free(tmp1);
			i++;
		}
	}
	// free(stock);
	free(str);
	return (rtn);
}
