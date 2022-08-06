/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:40:11 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/06 14:35:04 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer *tmp;

	if (lst == NULL || *lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	tmp = *lst;
	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	(*lst)->next = new;
	new->next = NULL;
	*lst = tmp;
}

void	ft_lstadd_front(t_lexer **lst, t_lexer *new)
{
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_lexer *lst)
{
	int	i;

	i = 0;
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_lexer	*ft_lstnew(char *content)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (node == NULL)
		return (NULL);
	node->content = content;
	printf("cmd == %s\n", node->content);    
	node->next = NULL;
	return (node);
}

t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
