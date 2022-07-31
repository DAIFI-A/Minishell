/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:22:34 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/25 18:37:47 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}