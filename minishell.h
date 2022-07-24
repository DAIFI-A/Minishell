#ifndef MINISHELL_H
#define MINISHELL_H

 #include <sys/types.h>
 #include <signal.h>
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

typedef struct s_args
{
    char    *arg;
    char    **cmd;
    char    **path;
    char    *str;
}   t_args;

typedef struct s_env
{
    char    *key;
    char    *value;
    struct env  *next;
}   t_env;

char	*get_path(char **envp, char *arg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);

#endif