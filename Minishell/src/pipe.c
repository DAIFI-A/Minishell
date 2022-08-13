/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:38:47 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/12 20:43:30 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../mini.h"

char	**env_str(t_env *env)
{
	char	*str;
	char	**envp;

	str = "";
	while (env)
	{
		str = ft_strjoin(str, env->key);
		str = ft_strjoin(str, "=");
		str = ft_strjoin(str, env->value);
		str = ft_strjoin(str, "$");
		env = env->next;
	}
	envp = ft_split(str, '$');
	return(envp);
}

char	*content_handler(t_lexer *arg, t_env *env, int i)
{
	char	*str;
	int		in;
	int		out;
	char	**envp;

	i = 0;
	str = ft_strdup("");
	while (arg && ft_strcmp(arg->content, "|"))
	{
		if (!ft_strcmp(arg->content, "<"))
		{
			arg = arg->next;
			in = open(arg->content, O_RDONLY, 00777);
		}
		else if (!ft_strcmp(arg->content, ">"))
		{
			arg = arg->next;
			out = open(arg->content, O_CREAT | O_WRONLY | O_TRUNC, 00777);
		}
		else
		{
			str = ft_strjoin(str, arg->content);
			str = ft_strjoin(str, " ");
		}
		arg = arg->next;
	}
	envp = env_str(env);
	execute_redir(envp, &env, str, in, out);
	return (str);
}

void	execute_redir(char **envp, t_env **env, char *str, int in, int out)
{
	char	**cmd;
	pid_t	cpid;

	cmd = ft_split(str, ' ');
	cpid = fork();
	if (cpid < 0)
	{
		g_exit_code = 1;
		ft_putendl_fd("fork error\n", 2);
	}
	if (cpid == 0)
	{
		dup2(in, STDIN_FILENO);
  		dup2(out, 1);
		execve(get_path(env, cmd[0]), cmd, envp);
	}
	waitpid(cpid, NULL, 0);
}

// void	execute_pipe(t_env *env, t_lexer *arg, int i, char **envp)
// {
// 	int		number_pipe;
// 	int		*fd;
// 	//pid_t	cpid;
// 	int		j;

// 	(void)envp;
// 	(void)env;
// 	number_pipe = i * 2;
// 	j = 0;
// 	fd = (int *)malloc(sizeof(number_pipe));
// 	content_handler(&arg);
// }