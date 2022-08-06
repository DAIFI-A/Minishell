/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:54:37 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/06 15:31:07 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env *tmp;

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

void	ft_lstadd_front_env(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize_env(t_env *lst)
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

t_env	*ft_lstnew_env(char *name, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	printf("%s=", node->name);
	printf("%s\n", node->value);
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
