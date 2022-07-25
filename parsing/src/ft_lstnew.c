/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:22:52 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/25 18:55:43 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_lexer	*ft_lstnew(char *content)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (node == NULL)
		return (NULL);
	node->content = ft_strdup(content);
	node->next = NULL;
	return (node);
}
