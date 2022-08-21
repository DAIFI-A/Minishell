/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:59:17 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/21 11:06:29 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_parser(t_lexer **lexer)
{
	t_lexer	*top;
	t_lexer	*tmp;

	top = (*lexer);
	while (*lexer)
	{
		if ((*lexer)->linked == 1)
		{
			(*lexer)->content
				= ft_strjoin((*lexer)->content, (*lexer)->next->content);
			(*lexer)->linked = (*lexer)->next->linked;
			tmp = (*lexer)->next->next;
			free((*lexer)->next->content);
			free(((*lexer)->next));
			(*lexer)->next = tmp;
			ft_parser(lexer);
		}
		(*lexer) = (*lexer)->next;
	}
	(*lexer) = top;
}
