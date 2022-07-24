#include"minishell.h"

char	*get_path(t_env *env, t_args *arg)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, arg->cmd[0]);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}