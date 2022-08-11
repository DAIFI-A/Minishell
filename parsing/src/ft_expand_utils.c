/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 09:17:21 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/11 09:48:09 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_util_tilde(t_env **env, t_env **head, char *str, int *i)
{
	char	*tmp;
	char	*rtn;

	rtn = ft_strdup("");
	*head = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->name, "HOME") == 0)
		{
			rtn = ft_strjoin(rtn, (*env)->value);
			break ;
		}
		*env = (*env)->next;
	}
	*env = *head;
	while (str[*i])
	{
		tmp = ft_char_to_str(str[*i]);
		rtn = ft_strjoin(rtn, tmp);
		free(tmp);
		(*i)++;
	}
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

int	ft_if_condition(char c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'))
		return (0);
	else
		return (1);
}
