#include"../minishell.h"

char	*get_path(t_env *env, t_args *arg)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while (env && env->key && ft_strncmp(env->key, "PATH", 4))
		env = env->next;
	paths = ft_split(env->value , ':');
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