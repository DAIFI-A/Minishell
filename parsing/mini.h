/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/21 12:37:57 by med-doba         ###   ########.fr       */
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

struct s_global
{
	int		id;
	pid_t	cpid;
	int		exit_status;
	char	*usr;
} var;

typedef struct lexer{
	char			*content;
	char			ch;
	int				linked;
	struct lexer	*next;
}t_lexer;

typedef struct environment
{
	char				*name;
	char				*value;
	int					index;
	int					yes;
	struct environment	*next;
}t_env;

//main
void	ft_header(void);
void	ft_handle(t_env *env);
void	ft_control_d(void);
void	ft_sighandler(int sig);
//expand
void	ft_expand(t_lexer **lexer, t_env *env);
char	*ft_parse_expand(char *str, t_env *env);
int		ft_put_dollar(char c);
char	*ft_tilde(char *str, t_env *env);
int		ft_if_condition(char c);
char	*ft_util_tilde(t_env **env, t_env **head, char *str, int *i);
char	*ft_join(char *rtn, char c);
char	*ft_join_value(t_env *env, char **stock, char *rtn);
int		ft_find_staus(char *str);
char	*ft_expand_status(char *str);
//envp
t_env	*ft_environment(char **envp, t_env *env);
void	ft_free_2d(char **ptr);
void	ft_while_env(t_env **env, char **envp, t_env **node, int *i);
//parser
void	ft_parser(t_lexer **lexer);
//utils
int		ft_check_case(char c);
int		ft_check_case_01(char c);
int		ft_check_case_02(char c);
int		ft_check_case03(char c);
char	*ft_char_to_str(char c);
int		ft_locate_char(char *str, char ch);
int		ft_find_char(char *str, char c);
int		ft_skip_withespace(char *str, int i);
//lexer
void	*ft_lexer(t_lexer **lexer, char *rtn, char **stock);
char	*ft_scan_quotes(char *str, char c, int *i);
char	*ft_scan_redirection(char *rtn, int *i, char c);
char	*ft_scan_pipe(char *str, char c, int *i);
int		ft_utils_pipe(char *str);
void	ft_add_node(t_lexer **lexer, char **stock, char ch, int linked);
int		ft_pipe(char **stock, char *str, int *i, t_lexer **lexer);
int		ft_redirection(char **stock, char *str, int *i, t_lexer **lexer);
void	ft_else(char *str, char **stock, int *i);
int		ft_string(t_lexer **lexer, char **stock, char *str, int *i);
char	*ft_qutes_util(char *str, char *rtn, int *i);
//node
void	ft_free_lst_env(t_env **head);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value, int yes);
void	ft_free_lst(t_lexer **head);
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew(char *content, int linked);
#endif
