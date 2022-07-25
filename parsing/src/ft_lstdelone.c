/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:22:00 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/25 18:37:24 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	*del(t_lexer *lst)
{
	free(lst->content);
	return (NULL);
}

void	ft_lstdelone(t_lexer *lst, void (*del)(void *))
{
	del(lst);
}
