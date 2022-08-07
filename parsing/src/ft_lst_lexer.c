/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:40:11 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/07 15:37:09 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer *tmp;

	if (*lst == NULL)
	{
		*lst = new;
		// printf("content cas null == %s\n", (*lst)->content);
		new->next = NULL;
		return ;
	}
	tmp = *lst;
	// printf("content cas lst == %s\n", (*lst)->content);
	// printf("content cas tmp == %s\n", (tmp)->content);
	while ((*lst)->next != NULL)
	{
		// printf("content cas while == %s\n", (*lst)->content);
		*lst = (*lst)->next;
	}
	(*lst)->next = new;
	new->next = NULL;
	*lst = tmp;
	// printf("content cas rewind == %s\n", (*lst)->content);
}

t_lexer	*ft_lstnew(char *content)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (node == NULL)
		return (NULL);
	node->content = ft_strdup(content);
	// printf("cmd == %s\n", node->content);
	node->next = NULL;
	return (node);
}
