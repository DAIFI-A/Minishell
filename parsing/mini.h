/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/12 08:43:46 by med-doba         ###   ########.fr       */
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
# include <unistd.h>

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
void	ft_handle(t_env *env);
//expand
void	ft_expand(t_lexer **lexer, t_env *env);
char	*ft_parse_expand(char *str, t_env *env);
int		ft_put_dollar(char c);
char	*ft_tilde(char *str, t_env *env);
int		ft_if_condition(char c);
char	*ft_util_tilde(t_env **env, t_env **head, char *str, int *i);
char	*ft_join(char *rtn, char c);
char	*ft_join_value(t_env *env, char **stock, char *rtn);
//envp
t_env	*ft_environment(char **envp, t_env *env);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
void	ft_free_2d(char **ptr);
void	ft_while_env(t_env **env, char **envp, t_env **node, int *i);
//lexer
int		ft_find_char(char *str, char c);
int		ft_skip_withespace(char *str, int i);
char	*ft_char_to_str(char c);
int		ft_check_case_01(char c);
int		ft_check_case_02(char c);
//parser
void	ft_parser(t_lexer **lexer, char *rtn, char **stock);
int		ft_check_case(char c);
char	*ft_scan_quotes(char *str, char c, int *i, int *j);
char	*ft_scan_redirection(char *rtn, int *i, char c);
char	*ft_scan_pipe(char *str, char c, int *i);
int		ft_utils_pipe(char *str);
void	ft_add_node(t_lexer **lexer, char **stock, char ch);
int		ft_pipe(char **stock, char *str, int *i, t_lexer **lexer);
int		ft_redirection(char **stock, char *str, int *i, t_lexer **lexer);
void	ft_else(char *str, char **stock, int *i, int *j);
int		ft_string(t_lexer **lexer, char **stock, char *str, int *i);
char	*ft_qutes_util(char *str, char *rtn, int *i, int *j);
//node
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew(char *content);
t_lexer	*ft_lstlast(t_lexer *lst);
#endif
