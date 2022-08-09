/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:31:15 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/09 16:39:22 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_expand(t_lexer **lexer, t_env *env)
{
	char		*tmp;
	t_lexer		*head;

	head = (*lexer);
	while ((*lexer))
	{
		if ((*lexer)->ch == '"' || (ft_find_char((*lexer)->content, '$') == 0))
		{
			tmp = ft_parse_expand((*lexer)->content, env);
			(*lexer)->content = ft_strdup(tmp);
			free(tmp);
		}
		if ((*lexer)->ch != '"' && (*lexer)->ch != '\'' && (ft_find_char((*lexer)->content, '~') == 0))
		{
			tmp = ft_tilde((*lexer)->content, env);
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
	char	*tmp;
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
			if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '_'))
			{
				while ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '_'))
				{
					tmp = ft_char_to_str(str[i]);
					stock = ft_strjoin(stock, tmp);
					free(tmp);
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
							break ;
						}
						env = env->next;
					}
					free(stock);
					stock = ft_strdup("");
					env = head;
				}
			}
			else if (ft_put_dollar(str[i]) == 0)
			{
				tmp = ft_char_to_str('$');
				rtn = ft_strjoin(rtn, tmp);
				free(tmp);
			}
		}
		if (str[i] == '\0')
			break ;
		if (str[i] != '$')
		{
			tmp = ft_char_to_str(str[i]);
			rtn = ft_strjoin(rtn, tmp);
			free(tmp);
			i++;
		}
	}
	free(str);
	return (rtn);
}

char	*ft_tilde(char *str, t_env *env)
{
	char	*rtn;
	char	*tmp;
	t_env	*head;
	int		i;

	i = 1;
	rtn = ft_strdup("");
	if ((str[0] == '~' && str[1] == '\0') || (str[0] == '~' && str[1] == '/'))
	{
		head = env;
		while (env)
		{
			if (ft_strcmp(env->name, "HOME") == 0)
			{
				rtn = ft_strjoin(rtn, env->value);
				break ;
			}
			env = env->next;
		}
		head = env;
		while (str[i])
		{
			tmp = ft_char_to_str(str[i]);
			rtn = ft_strjoin(rtn, tmp);
			free(tmp);
			i++;
		}
		free(str);
		return (rtn);
	}
	else
		rtn = ft_strdup(str);
	free(str);
	return (rtn);
}

int	ft_put_dollar(char c)
{
	if (!(c >= 'A' && c <= 'Z')
		&& !(c >= 'a' && c <= 'z')
		&& !(c >= '0' && c <= '9')
		&& !(c == '_' && c == '$'))
		return (0);
	else
		return (1);
}
