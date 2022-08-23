/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:38:47 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/17 16:15:36 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../mini.h"

char	**env_str(t_env *env)
{
	char	*str;
	char	**envp;

	str = ft_strdup("");
	while (env)
	{
		str = ft_strjoin(str, env->key);
		str = ft_strjoin(str, "=");
		str = ft_strjoin(str, env->value);
		str = ft_strjoin(str, "$");
		env = env->next;
	}
	envp = ft_split(str, '$');
	free(str);
	return(envp);
}

char	*redirection_handler(t_lexer **arg, t_fds *fds, char *str)
{
	int		i;

	i = 0;
	while ((*arg) && (ft_strcmp((*arg)->content, "|") || (*arg)->ch == '"' || (*arg)->ch == '\''))
	{
		if (!ft_strcmp((*arg)->content, "<<"))
		{
			(*arg) = (*arg)->next;
			close(fds->in);
			fds->in = her_doc((*arg));
			i = 1;
		}
		else if (!ft_strcmp((*arg)->content, "<"))
		{
			(*arg) = (*arg)->next;
			close(fds->in);
			fds->in = open((*arg)->content, O_RDWR, 0777);
		}
		else if (!ft_strncmp((*arg)->content, ">", 1))
		{
			(*arg) = (*arg)->next;
			close(fds->out);
			if (!ft_strcmp((*arg)->content, ">>"))
				fds->out = open((*arg)->content, O_APPEND | O_CREAT | O_WRONLY, 00777);
			else
				fds->out = open((*arg)->content, O_CREAT | O_WRONLY | O_TRUNC, 00777);
		}
		else
		{
			str = ft_strjoin(str, (*arg)->content);
			str = ft_strjoin(str, " ");
		}
		(*arg) = (*arg)->next;
	}
	if (i == 1)
		str = ft_strjoin(str, "tmp");
	return (str);
}

void	content_handler(t_lexer **arg, t_env **env, t_fds *fds)
{
	char	*str;
	t_lexer	*tmp;
	int		tmp_in;
	int		tmp_out;
	int		i;

	tmp = *arg;
	i = 0;
	str = ft_strdup("");
	tmp_in = dup(0);
	tmp_out = dup(1);
	str = redirection_handler(arg, fds, str);
	if (*str == '\0')
		return (printf("command not found\n"), var.exit_status = 127, free(str));
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	execute_redir(tmp, env, fds, str);
	free(str);
	unlink("tmp");
}

void	execute_redir(t_lexer *arg, t_env **env, t_fds *fds, char *str)
{
	char	**cmd;
	int		tmp_in;
	int		tmp_out;

	if (fds->in < 0 || fds->out < 0)
		return (var.exit_status = 1, ft_putendl_fd("fd rerror", 2));
	cmd = ft_split(str, ' ');
	tmp_in = dup(0);
	tmp_out = dup(1);
	dup2(fds->in, STDIN_FILENO);
	dup2(fds->out, STDOUT_FILENO);
	close(fds->in);
	close(fds->out);
	if (check_type(cmd[0]))
		builting(env, arg);
	else
		execute(cmd, env);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	ft_free_2d(cmd);
}

void	execute(char **cmd, t_env **env)
{
	char	**envp;
	int		stat;

	stat = 0;
	var.cpid = fork();
	var.id = 1;
	if (var.cpid < 0)
		return (var.exit_status = 1, ft_putendl_fd("fork error", 2), ft_free_2d(cmd));
	if (var.cpid == 0)
	{
		envp = env_str(*env);
		if (execve(get_path(cmd[0]), cmd, envp) == -1 || get_path(cmd[0]) == NULL)
			return (ft_putendl_fd("command not found", 2), ft_free_2d(cmd), exit(127));
		ft_free_2d(envp);
	}
	wait(&stat);
	var.exit_status = WEXITSTATUS(stat);
}

void	execute_pipe(t_env *env, t_lexer *arg, t_fds *fds, int i)
{
	int		j;
	int		tmp_in;
	int		tmp_out;

	j = 0;
	fds->fd = (int *)malloc((i * 2) * sizeof(int));
	tmp_in = dup(0);
	tmp_out = dup(1);
	while (j < i * 2)
	{
		pipe(fds->fd + j);
		j += 2;
	}
	i = i + 1;
	pipe_handler(fds, arg, env, i);
	j = 0;
	while (j < i + 1)
	{
		close(fds->fd[(j - 1) * 2]);
		j++;
	}
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	close(fds->in);
	close(fds->out);
	free(fds->fd);
}

void	pipe_handler(t_fds *fds, t_lexer *arg, t_env *env, int i)
{
	int		j;

	j = -1;
	while (arg && ++j < i)
	{
		if (j == 0)
		{
			fds->in = dup(0);
			fds->out =  dup(fds->fd[(j * 2) + 1]);
		}
		else if (j < i && j != i - 1)
		{
			fds->out = dup(fds->fd[(j * 2) + 1]);
			fds->in = dup(fds->fd[(j - 1) * 2]);
		}
		else if (j == i - 1)
		{
			fds->in = dup(fds->fd[(j - 1) * 2]);
			fds->out = dup(1);
		}
		content_handler(&arg, &env, fds);
		if (arg && arg->next != NULL)
			arg = arg->next;
		close(fds->fd[(j * 2) + 1]);
	}
}