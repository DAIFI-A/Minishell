#ifndef MINISHELL_H
#define MINISHELL_H

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
typedef struct s_args
{
    char    *arg;
    char    **cmd;
    char    **paths;
    char    *str;
}   t_args;

typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env  *next;
}   t_env;

char	*get_path(t_env *env, t_args *arg);
char	*get_keys(char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	pwd_env(char **str, t_env *env);
void	export_env(t_env **env, t_args *arg, char **str);
void	echo(t_env *env, char **cmd, t_args *arg);
void	cd_home(t_env *env, t_args *arg);
void	cd(t_env *env, char **str, t_args *arg);
void	ft_lstadd_back_prime(t_env **lst, t_env *node);
t_env   *ft_lst_new1(char *key, char *value);
t_env	*create_env(char **envp);
t_env	*env_i(t_env *env);
void	unset_env(t_env **env, char **str);
void	env_env(char **str, t_env *env);

#endif