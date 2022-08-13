/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:42:09 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/13 21:27:38 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../mini.h"

int	her_doc(t_lexer *arg)
{
	char	*s;
	int		tmp;

	s = get_next_line(0);
	tmp = open("tmp", O_CREAT | O_APPEND | O_RDWR, 00777);
	(void)arg;
	while (1)
	{
		s = get_next_line(0);
		if (s == NULL)
			break;
	}
	write(tmp, s, 2);
	return (tmp);
}