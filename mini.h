/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:50 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/18 09:20:44 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <paths.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

struct s_jehgrouehrgou
{
	int		id;
	pid_t	cpid;
	char	*usr;
	int		exit_status;
} var;

typedef struct lexer{
	char			*content;
	char			ch;
	struct lexer	*next;
	int				flag;
}	t_lexer;

typedef struct fds
{
	int		in;
	int		out;
	int		*fd;
}	t_fds;

typedef struct environment
{
	char				*key;
	char				*value;
	int					index;
	struct environment	*next;
}	t_env;

//utils
void	ft_header(void);
void	ft_handle(t_env *env);
//expand
void	ft_expand(t_lexer **lexer, t_env *env);
char	*ft_parse_expand(char *str, t_env *env);
int		ft_put_dollar(char c);
char	*ft_tilde(char *str, t_env *env);
char	*ft_util_tilde(t_env **env, t_env **head, char *str, int *i);
int		ft_if_condition(char c);
char	*ft_join_value(t_env *env, char **stock, char *rtn);
char	*ft_join(char *rtn, char c);
//mini.c&&add
int		ft_multiple_check(char *arg);
void	ft_print_exported(t_env **env);
void	ft_add_export(char *str, t_env **env);
void	ft_free_lst(t_lexer **head);
void	ft_init_global(void);
//envp
t_env	*ft_environment(char **envp, t_env *env);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
void	ft_free_2d(char **ptr);
//lexer
int		ft_find_char(char *str, char c);
int		ft_skip_withespace(char *str, int i);
char	*ft_char_to_str(char c);
int		ft_check_case_01(char c);
int		ft_check_case_02(char c);
int		ft_utils_pipe(char *str);
int		ft_find_char(char *str, char c);
int		ft_check_case(char c);
//parser
void	ft_parser(t_lexer **lexer, char *str, char **stock);
int		ft_check_case(char c);
char	*ft_scan_quotes(char *str, char c, int *i, int *j);
char	*ft_scan_redirection(char *rtn, int *i, char c);
char	*ft_scan_pipe(char *str, char c, int *i);
int		ft_utils_pipe(char *str);
int		ft_pipe(char **stock, char *str, int *i, t_lexer **lexer);
int		ft_redirection(char **stock, char *str, int *i, t_lexer **lexer);
void	ft_else(char *str, char **stock, int *i, int *j);
int		ft_string(t_lexer **lexer, char **stock, char *str, int *i);
char	*ft_qutes_util(char *str, char *rtn, int *i, int *j);
void	ft_add_node(t_lexer **lexer, char **stock, char ch);
//node
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew(char *content);
t_lexer	*ft_lstlast(t_lexer *lst);
//builts_in
void	ft_sort_env(t_env **env);
//execution part
void	cd_home(t_env *env);
int		check_type(char *arg);
void	builting(t_env **env, t_lexer *arg);
void	one_cmd(t_env **env, t_lexer *arg, char **envp, char *str);
void	check_cmd(t_env **env, t_lexer *arg, t_fds *fd);
void	pwd_env(void);
char	*get_path(char *cmd);
void	unset_env(t_env **env, t_lexer *arg);
t_env	*unset(t_env *env, t_env *tmp, t_lexer *arg);
void	free_env(t_env *env);
void	echo(t_lexer *arg);
void	export_env(t_env **env, t_lexer *arg);
void	set_env_existed(t_env **env, t_lexer *arg, t_env **lst);
void	cd(t_env *env, t_lexer *arg);
t_env	*ft_lst_new1(char *key, char *value);
void	ft_lstadd_back_prime(t_env **lst, t_env *node);
char	*get_keys(char *str, int c);
void	env_env(t_env *env);
void	execute_pipe(t_env *env, t_lexer *arg, t_fds *fds, int i);
t_lexer	*ft_lst_new_prime(char *str);
void	content_handler(t_lexer **arg, t_env **env, t_fds *fds);
void	execute_redir(t_lexer *arg, t_env **env, t_fds *fds, char *str);
int		her_doc(t_lexer *arg);
char	*get_next_line(int fd);
void	update_pwd(t_env **lst, char *home);
#endif
