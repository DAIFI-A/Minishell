/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/07/25 18:32:57 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <signal.h>

typedef struct lexer{
	char			*content;
	int				index;
	int				len;
	struct lexer	*next;
}t_lexer;

void	ft_handle(void);
//utils
void	ft_header(void);
void	ft_lexer(char *str, t_lexer *lexer);
//lexer
int	ft_check_case(char c);
#endif
