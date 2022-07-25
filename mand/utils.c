/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:30:18 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/25 16:10:11 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lst_new1(char *key, char *value)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = key;
	lst->value = value;
	lst->next = NULL;
	return(lst);
}

void	ft_lstadd_back_prime(t_env **lst, t_env *node)
{
	t_env	*head;

	head = *lst;
	if (!head)
		head = node;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = node;
	}
}