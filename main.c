#include"minishell.h"

void	check_path(t_env *env, t_args *arg)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = env;
	while(lst)
	{
		if (!(ft_strncmp(lst->key, "PATH", 4)))
		{
			if (lst->value)
			{
				arg->path = ft_split(lst->value, ':');
				i = 1;
			}
			break ;
		}		
		lst = lst->next;
	}
	if (i != 1)
	{
		ft_putendl_fd("PATH not found", 2);
		exit(1);
	}
}

int	check_type(t_env *env, char *arg)
{
	char	**splited;
	int		id;

	splited = ft_split(str, ' ');
	if (!ft_strncmp(splited[0], "pwd"))
		return (1);
	else if (!ft_strncmp(splited[0], "export"))
		return (1);
	else if (!ft_strncmp(splited[0], "unset"))
		return (1);
	else if (!ft_strncmp(splited[0], "env"))
		return (1);
	else if (!ft_strncmp(splited[0], "exit"))
		return (1);
	else if (!ft_strncmp(splited[0], "cd"))
		return (1);
	else if (!ft_strncmp(splited[0], "echo"))
		return (1);
	return (0);
}

void	builting(t_env *env, t_args *arg)
{
	char	**cmd;

	cmd = ft_split(arg->str, ' ');
	else if (!ft_strncmp(cmd[0], "pwd"))
		pwd(env);
	else if (!ft_strncmp(cmd[0], "cd"))
		cd(env, cmd[1], arg);
	else if (!ft_strncmp(cmd[0], "unset"))
		unset(env);
	else if (!ft_strncmp(cmd[0], "echo"))
		echo(env, cmd, arg);
	else if (!ft_strncmp(cmd[0], "export"))
		export_env(&env, arg, cmd);
	else if (!ft_strncmp(cmd[0], "env"))
		env(&env, arg, cmd);
	else if (!ft_strncmp(cmd[0], "exit"))
	{
		if (cmd[1] != NULL)
			exit0(env, arg);
		else
			exit1(env, arg);
	}

}

void	echo(t_env *env, char **cmd, t_args *arg)
{
	int		i;
	char	*output;

	i = 0;
	while (cmd[i])
	{
		if (cmd[1][0] == '-' && cmd[1][1] == 'n')
		{
			i = 2;
			while (cmd[i])
			{
				output = ft_strjoin(output, cmd[i])
				i++;
			}
			printf("%s", output);
		}
		//else if (expand for $ sequence)
		else
		{
			while (cmd[i])
			{
				output = ft_strjoin(output, cmd[i])
				i++;
			}
			printf("%s\n", output);
		}
}

void	pwd(t_env *env)
{
	char	cwd[1024];

	if (!(getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	else
		ft_putendl_fd("Unable to get working directory");
}

void	cd_home(t_env *env, t_args *arg)
{
	t_env	*lst;
	char	*home;
	char	*old_pwd;
	char	*pwd;

	while (lst)
	{
		if (!ft_strncmp(lst->key, "HOME"))
		{
			if (chdir(lst->value))
			{
				ft_putendl_fd("Home not set", 1);
				return ;
			}
			home = lst->value;
			break ;
		}
		if (!home == NULL)
			ft_putendl_fd("Command not found", 1);
		lst = lst->next;
	}
	lst = env;
	while (lst)
	{
		if (!ft_strcmp(lst->key, "PWD"))
		{
			if (lst->value)
				OLDPWD = lst->value;
			lst->value = home;
			break ;
		}
		lst = lst->next;
	}
	lst = env;
	while (lst)
	{
		if (!ft_strcmp(lst->key, "OLDPWD"))
		{
			lst->value = home;
			break ;
		}
		lst = lst->next;
	}
}

void	cd(t_env *env, char *str, t_args *arg)
{
	char	*old_pwd;
	char	*cwd;

	old_pwd = NULL;
	cwd = NULL;
	if (str == NULL)
		cd_home(env, arg)
	else 
	{
		old_pwd = getcwd(cwd, 9999));
		if (chdir(str))
		{
			ft_putendl_fd("No such file or directory", 2);
			//exit_status = 1; => for $? expandation 
			return ;
		}
		lst = env;
		while (lst)
		{
			if (!ft_strcmp(lst->key, "PWD"))
			{
				if (lst->value)
					old_pwd = lst->value;
				cwd = NULL;
				lst->value = getcwd(cwd, 9999);
				break ;
			}
			lst = lst->next;
		}
		lst = env;
		while (lst)
		{
			if (!ft_strcmp(lst->key, "OLDPWD"))
			{
				lst->value = old_pwd;
				break ;
			}
			lst = lst->next;
		}
	}
}

void	export_env(t_env *env, t_args *arg, char **str)
{
	//problem if we put just "export something" without = value; 
	int		i;
	t_env	*lst;

	i = 1;
	lst = env;
	if (str[i])
	{
		if (!lst)
			lst = ft_lstnew(str[i])
		else
			ft_lstadd_back(lst, str[i]);
	}
}

int	one_cmd(t_env *env, t_args *arg)
{
	int		i;

	i = 0;
	while (arg->cmd[i])
		i++;
	if (i == 1)
	{
		i = 0;
		if (check_type(env, arg->cmd[i]))
		{
			builting(env, arg->cmd[i]);
			return (1);
		}
	}
	else if (i == 0)
		return (1);
	return (0);
}

void	check_cmd(t_env *env, t_args *arg)
{
	t_env	*lst;
	int		i;

	i = 0;
	check_path(env, arg);
	if (one_cmd(env, arg))
		return ;
}


char	*get_keys(char *str, int c)
{
	char	*h;
	char	a;
	int		j;

	h = str;
	j = 0;
	a = (char) c;
	while (h[j] != a)
		j++;
	if (h[j] + 2 == 0)
		return (str);
	else
	{
		h[j] = 0;
		return (h);
	}
	return (0);
}

void	create_env(t_env **env, char **envp, int i)
{
	t_env	*lst;
	char	*value;
	char	*key
	int		j;

	j = 0;
	*env = NULL;
	lst = NULL;
	while (i > 0)
	{
		value = ft_strdup(envp[j]);
		value = ft_strchr(value, '=') + 1;
		key = ft_strdup(envp[j]);
		key = get_keys(key, '=');
		lst = ft_lstnew(key, value);
		ft_lstadd_back(env, lst);
		j++;
		i--;
	}
}

int main(int argc, char const *argv[], char *envp[])
{
	t_args	arg;
	t_env	env;
	int		i;
	
	i = 0;
	while (envp[i])
		i++;
	create_env(&env, envp, i);
	while(1)
	{
		arg->str = readline("Minishell> ");
		arg->cmd = ft_split(arg->str, '|');
		check_cmd(env, arg);
	}
	return 0;
}
