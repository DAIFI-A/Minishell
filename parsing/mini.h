/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/06 15:16:57 by med-doba         ###   ########.fr       */
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
	char			pipe;
	struct lexer	*next;
}t_lexer;

typedef struct environment
{
	char				*name;
	char				*value;
	struct environment	*next;
}t_env;

void	ft_handle(void);
//utils
void	ft_header(void);
void	ft_lexer(char *str, t_lexer **lexer);
//envp
t_env	*ft_environment(char **envp, t_env *env);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstadd_front_env(t_env **lst, t_env *new);
int		ft_lstsize_env(t_env *lst);
t_env	*ft_lstnew_env(char *name, char *value);
t_env	*ft_lstlast_env(t_env *lst);
//lexer
int		ft_check_case(char c);
int		ft_skip_withespace(char *str, int i);
char	*ft_char_to_str(char c);
//parser
void	ft_parser(t_lexer *lexer, char *rtn);
int		ft_locate_char(char *str, char c);
int		ft_scan(char *rtn);
int		ft_check_stock(char *str);
int		ft_check_case_2(char c);
char	*ft_scan_quotes(char *str, char c, int *i);
char	*ft_scan_redirection(char *rtn, int *i, char c);
char	*ft_scan_pipe(char *str, char c, int *i);

//node
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
void	ft_lstadd_front(t_lexer **lst, t_lexer *new);
void	ft_lstclear(t_lexer **lst, void (*del)(void*));
void	ft_lstdelone(t_lexer *lst, void (*del)(void *));
t_lexer	*ft_lstlast(t_lexer *lst);
t_lexer	*ft_lstnew(char *content);
int		ft_lstsize(t_lexer *lst);
#endif
