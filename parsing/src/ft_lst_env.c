/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:54:37 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/15 16:33:25 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

t_env	*ft_lstnew_env(char *name, char *value, int yes)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->name = ft_strdup(name);
	if (value)
		node->value = ft_strdup(value);
	node->yes = yes;
	node->next = NULL;
	return (node);
}
