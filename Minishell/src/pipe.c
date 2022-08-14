/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:38:47 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/14 10:48:36 by adaifi           ###   ########.fr       */
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

void	content_handler(t_lexer *arg, t_env *env, int i)
{
	char	*str;
	int		in;
	int		out;
	t_lexer	*tmp;

	i = 0;
	str = ft_strdup("");
	tmp = arg;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	while (arg)
	{
		if (!ft_strcmp(arg->content, "<"))
		{
			arg = arg->next;
			in = open(arg->content, O_RDWR, 0777);
		}
		else if (!ft_strcmp(arg->content, ">"))
		{
			arg = arg->next;
			close(out);
			out = open(arg->content, O_CREAT | O_WRONLY | O_TRUNC, 00777);
		}
		else if (!ft_strcmp(arg->content, ">>"))
		{
			arg = arg->next;
			out = open(arg->content, O_APPEND | O_CREAT | O_WRONLY, 00777);
		}
		else if (!ft_strcmp(arg->content, "<<"))
		{
			arg = arg->next;
			her_doc(arg);
			str = ft_strjoin(str, " tmp");
		}
		else
		{
			str = ft_strjoin(str, arg->content);
			str = ft_strjoin(str, " ");
		}
		arg = arg->next;
	}
	if (*str == '\0')
		return (printf("command not found\n"), g_exit_code = 127,free(str));
	// if (i > 0)
	// 	execute_pipe(env, arg, i);
	// else
	execute_redir(tmp, &env, str, in, out);
	unlink("tmp");
}

void	execute_redir(t_lexer *arg, t_env **env, char *str, int in, int out)
{
	char	**cmd;
	pid_t	cpid;
	char	**envp;

	cmd = ft_split(str, ' ');
	if (in < 0 || out < 0)
		return (g_exit_code = 1, printf("fd rerror\n"), free(str));
	int tmp_in, tmp_out;
	tmp_in = dup(0);
	tmp_out = dup(1);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	if (check_type(cmd[0]))
		builting(env, arg);
	else
	{
		cpid = fork();
		if (cpid < 0)
			return (g_exit_code = 1, ft_putendl_fd("fork error\n", 2));
		if (cpid == 0)
		{
			if (get_path(env, cmd[0]) == NULL)
			{
				g_exit_code = 127;
				printf("command not found\n");
			}
			envp = env_str(*env);
			execve(get_path(env, cmd[0]), cmd, envp);
		}
		waitpid(cpid, NULL, 0);
	}
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	execute_pipe(t_env *env, t_lexer *arg, int i, char **envp)
{
	int		number_pipe;
	int		*fd;
	int		j;

	(void)envp;
	(void)env;
	(void)arg;
	number_pipe = i * 2;
	j = 0;
	fd = (int *)malloc(number_pipe * sizeof(int));
	while (j <= number_pipe)
	{
		if (pipe(fd + j * 2) < 0)
			return (ft_putendl_fd("pipe errors", 2), free(fd), exit(1));
		j++;
	}
}
// 	j = 0;
// 	while(arg && j <= number_pipe)
// 	{

// 	}
// }