/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/11 14:41:42 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

int	g_exit_code;

typedef struct lexer{
	char			*content;
	char			ch;
	struct lexer	*next;
	int				flag;
}	t_lexer;

typedef struct environment
{
	char				*key;
	char				*value;
	struct environment	*next;
}	t_env;

//utils
void	ft_header(void);
void	ft_handle(t_env *env, char **envp);
//expand
void	ft_expand(t_lexer **lexer, t_env *env);
char	*ft_parse_expand(char *str, t_env *env);
int		ft_put_dollar(char c);
char	*ft_tilde(char *str, t_env *env);
//envp
t_env	*ft_environment(char **envp, t_env *env);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
void	ft_free_2d(char **ptr);
//lexer
int		ft_find_char(char *str, char c);
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
//execution part
void	cd_home(t_env *env);
int		check_type(char *arg);
void	builting(t_env **env, t_lexer *arg);
void	one_cmd(t_env **env, t_lexer *arg, char **envp, char *str);
void	check_cmd(t_env **env, t_lexer *arg, char **envp);
void	pwd_env(t_lexer *arg);
char	*get_path(t_env **env, char *cmd);
void	unset_env(t_env **env, t_lexer *arg);
void	echo(t_lexer *arg);
void	export_env(t_env **env, t_lexer *arg);
void	cd(t_env *env, t_lexer *arg);
t_env	*ft_lst_new1(char *key, char *value);
void	ft_lstadd_back_prime(t_env **lst, t_env *node);
char	*get_keys(char *str, int c);
void	env_env(t_lexer *arg, t_env *env);
void	execute_pipe(t_env *env, t_lexer *arg, int i, char **envp);
t_lexer	*ft_lst_new_prime(char *str);
#endif
