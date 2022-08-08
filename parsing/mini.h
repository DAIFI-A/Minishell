/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/08 08:56:15 by med-doba         ###   ########.fr       */
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
 #include <unistd.h>

typedef struct lexer{
	char			*content;
	char			ch;
	struct lexer	*next;
}t_lexer;

typedef struct environment
{
	char				*name;
	char				*value;
	struct environment	*next;
}t_env;

//utils
void	ft_header(void);
void	ft_handle(void);
//envp
t_env	*ft_environment(char **envp, t_env *env);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
void	ft_free_2d(char **ptr);
//lexer
int		ft_skip_withespace(char *str, int i);
char	*ft_char_to_str(char c);
//parser
void	ft_parser(t_lexer **lexer, char *rtn);
int		ft_check_case(char c);
char	*ft_scan_quotes(char *str, char c, int *i, int *j);
char	*ft_scan_redirection(char *rtn, int *i, char c);
char	*ft_scan_pipe(char *str, char c, int *i);
int		ft_utils_pipe(char *str);
//node
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew(char *content);
t_lexer	*ft_lstlast(t_lexer *lst);
#endif
