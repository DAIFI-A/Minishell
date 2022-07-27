#include"../minishell.h"

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
				arg->paths = ft_split(lst->value, ':');
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

	splited = ft_split(arg, ' ');
	if (!ft_strncmp(splited[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(splited[0], "export", 7))
		return (1);
	else if (!ft_strncmp(splited[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(splited[0], "env", 4))
		return (1);
	else if (!ft_strncmp(splited[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(splited[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(splited[0], "echo", 5))
		return (1);
	return (0);
}

void	builting(t_env *env, t_args *arg)
{
	char	**cmd;

	cmd = ft_split(*(arg->cmd), ' ');
	if (!ft_strncmp(cmd[0], "pwd", 4))
		pwd_env(env);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		cd(env, cmd[1], arg);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		unset_env(env, cmd);
	else if (!ft_strncmp(cmd[0], "echo", 5))
		echo(env, cmd, arg);
	else if (!ft_strncmp(cmd[0], "export", 7))
		export_env(env, arg, cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		env_env(env);
	// else if (!ft_strncmp(cmd[0], "exit", 5))
	// {
	// 	if (cmd[1] != NULL)
	// 		exit0(env, arg);
	// 	else
	// 		exit1(env, arg);
	//}

}

void	env_env(t_env *env)
{
	while(env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
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
				output = ft_strjoin(output, cmd[i]);
				i++;
			}
			printf("%s", output);
		}
		//else if (expand for $ sequence)
		else
		{
			while (cmd[i])
			{
				output = ft_strjoin(output, cmd[i]);
				i++;
			}
			printf("%s\n", output);
		}
	}
}

void	pwd_env(t_env *env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	else
		ft_putendl_fd("Unable to get working directory", 2);
}

void	cd_home(t_env *env, t_args *arg)
{
	t_env	*lst;
	char	*home;
	char	*old_pwd;
	char	*pwd;

	lst = env;
	while (env)
	{
		if(env->key)
		{
			if (!ft_strncmp(env->key, "HOME", 5))
			{
				if (chdir(env->value))
				{
					ft_putendl_fd("Home not set", 1);
					return ;
				}
				home = env->value;
				break ;
			}
		}
		env = env->next;
	}
	while (lst)
	{
		if(lst->key)
		{
			if (!ft_strncmp(lst->key, "PWD", 3))
			{
				if (lst->value)
					old_pwd = lst->value;
				lst->value = ft_strdup(home);
				break ;
			}
		}
		lst = lst->next;
	}
	lst = env;
	while (lst)
	{
		if(lst->key)
		{
			if (!ft_strncmp(lst->key, "OLDPWD", 6))
			{
				lst->value = ft_strdup(old_pwd);
				break ;
			}
		}
		lst = lst->next;
	}
}

void	cd(t_env *env, char *str, t_args *arg)
{
	char	*old_pwd;
	char	cwd[1024];
	t_env	*lst;

	old_pwd = NULL;
	lst = env;
	if (str == NULL)
		cd_home(env, arg);
	else 
	{
		if (chdir(str))
		{
			ft_putendl_fd("No such file or directory", 2);
			//exit_status = 1; => for $? expandation 
			return ;
		}
		while (lst)
		{
			if (lst->key)
			{
				if (!ft_strncmp(lst->key, "PWD", 4))
				{
					if (lst->value)
						old_pwd = lst->value;
					lst->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
					break ;
				}
			}
			lst = lst->next;
		}
		lst = env;
		while (lst)
		{
			if (lst->key)
			{
				if (!ft_strncmp(lst->key, "OLDPWD", 7))
				{
					lst->value = old_pwd;
					break ;
				}
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
	char	*value;
	char	*key;

	i = 1;
	lst = env;
	if (str[i] == NULL)
	{
		while (env)
		{
			if (env->key && env->value)
				printf("declare -x %s=\"%s\"\n", env->key, env->value);
			env = env->next;
		}
	}
	while (str[i])
	{
		while (env && str[i])
		{
			if (env->key)
			{
				key = ft_strdup(str[i]);
				key = get_keys(key, '=');
				if (!key)
					return ;
				if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
				{
					env->value = ft_strdup(ft_strchr(str[i], '=') + 1); 
					break ;
				}
			}
			env = env->next;
		}
		if (env == NULL)
		{
			env = lst;
			key = ft_strdup(str[i]);
			key = get_keys(key, '=');
			value = ft_strdup(str[i]);
			value = ft_strchr(value, '=') + 1;
			lst = ft_lst_new1(key, value);
			ft_lstadd_back_prime(&env, lst);
		}
		i++;
	}
}

int	one_cmd(t_env *env, t_args *arg, char *envp[])
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
			builting(env, arg);
			return (1);
		}
		else
			execve(get_path(env, arg), &arg->cmd[i], envp);
	}
	else if (i == 0)
		return (1);
	return (0);
}

void unset_env(t_env *env, char **str)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*tmp;
	t_env	*lst;
	t_env	*env_back;

	i = 1;
	tmp = NULL;
	while (str[i])
	{
		env_back = env;
		while(env)
		{
			if (env->key)
			{
				if (ft_strncmp(env->key, str[i], ft_strlen(env->key)))
				{
					lst = ft_lst_new1(env->key, env->value);
					ft_lstadd_back_prime(&tmp, lst);
				}
			}
			env = env->next;
		}
		env = env_back;
		while (env)
		{
			env_back = env;
			free(env);
			env = env_back->next;
		}
		env = tmp;
		tmp = NULL;
		i++;
	}
	env_env(env);
}

void	check_cmd(t_env *env, t_args *arg, char	*envp[])
{
	t_env	*lst;
	int		i;

	i = 0;
	
//	check_path(env, arg);
	if (one_cmd(env, arg, envp))
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
}

t_env	*create_env(char **envp)
{
	t_env	*lst;
	char	*value;
	char	*key;
	t_env	*env;
	int 	i;

	i = 0;
	// env = (t_env *)malloc(sizeof(t_env));
	// if (!env)
	// 	return (printf("unable to allocate memory\n"), NULL);
	env = NULL;
	while (envp[i] != NULL)
	{
		value = ft_strdup(envp[i]);
		value = ft_strchr(value, '=') + 1;
		key = ft_strdup(envp[i]);
		key = get_keys(key, '=');
		if (value && key)
			lst = ft_lst_new1(key, value);
		ft_lstadd_back_prime(&env, lst);
		i++;
	}
	return(env);
}

t_env	*env_i(t_env *env)
{
	char	*value;
	char	*key;
	t_env	*lst;
	t_env	*lst1;
	char	*value1;
	char	*key1;
	char	cwd[1024];

	value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	key = ft_strdup("PATH=");
	value1 = ft_strdup(getcwd(cwd, sizeof(cwd)));
	key1 = ft_strdup("PWD=");
	env = ft_lst_new1(key, value);
	lst1 = ft_lst_new1(key1, value1);
	ft_lstadd_back_prime(&env, lst1);
	return (env);
}

int main(int argc, char const *argv[], char *envp[])
{
	t_args	*arg;
	t_env	*env;
	int		i;
	
	i = 0;
	arg = (t_args *)malloc(sizeof(t_args));
	if (!envp[i])
		env = env_i(env);
	if (envp[i])
		env = create_env(envp);
	while(1)
	{
		arg->str = readline("Minishell> ");
		arg->cmd = ft_split(arg->str, '|');
		check_cmd(env, arg, envp);
	}
	return 0;
}
