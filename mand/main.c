#include"../minishell.h"
#include<string.h>

int	check_type(char *arg)
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

void	builting(t_env **env, t_args *arg)
{
	char	**cmd;

	cmd = ft_split(*(arg->cmd), ' ');
	if (!ft_strncmp(cmd[0], "pwd", 4))
		pwd_env(*env);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		cd(*env, cmd[1], arg);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		unset_env(env, cmd);
	else if (!ft_strncmp(cmd[0], "echo", 5))
		echo(*env, cmd, arg);
	else if (!ft_strncmp(cmd[0], "export", 7))
		export_env(env, arg, cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		env_env(*env);
	// else if (!ft_strncmp(cmd[0], "exit", 5))
	// {
	// 	if (cmd[1] != NULL)
	// 		exit0(env, arg);
	// 	else
	// 		exit1(env, arg);
	//}

}

int	one_cmd(t_env **env, t_args *arg, char *envp[])
{
	int		i;

	i = 0;
	while (arg->cmd[i])
		i++;
	if (i == 1)
	{
		i = 0;
		if (check_type(arg->cmd[i]))
		{
			builting(env, arg);
			return (1);
		}
		else
		{
			execvp(arg->cmd[i], &arg->cmd[i]);
			return(1);
		}
	}
	else if (i == 0)
		return (1);
	return (0);
}

void	check_cmd(t_env **env, t_args *arg, char	*envp[])
{
	t_env	*lst;
	int		i;

	i = 0;
	
//	check_path(env, arg);
	if (one_cmd(env, arg, envp))
		return ;
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
		check_cmd(&env, arg, envp);
	}
	return 0;
}
