/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:21:00 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/25 18:36:57 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	del(t_lexer *lst)
{
	free(lst->content);
}

void	ft_lstclear(t_lexer **lst, void (*del)(void*))
{
	t_lexer	*my;

	while ((*lst)->next != NULL)
	{
		del(*lst);
		my = (*lst)->next;
		free(*lst);
		*lst = my;
	}
}
