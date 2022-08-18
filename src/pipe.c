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

void	content_handler(t_lexer **arg, t_env **env, t_fds *fds)
{
	char	*str;
	t_lexer	*tmp;
	int		tmp_in;
	int		tmp_out;

	tmp = *arg;
	str = "";
	tmp_in = dup(0);
	tmp_out = dup(1);
	while ((*arg) && ft_strcmp((*arg)->content, "|"))
	{
		if (!ft_strcmp((*arg)->content, "<"))
		{
			(*arg) = (*arg)->next;
			close(fds->in);
			fds->in = open((*arg)->content, O_RDWR, 0777);
		}
		else if (!ft_strcmp((*arg)->content, "<<"))
		{
			(*arg) = (*arg)->next;
			close(fds->in);
			fds->in = her_doc((*arg));
		}
		else if (!ft_strcmp((*arg)->content, ">"))
		{
			(*arg) = (*arg)->next;
			close(fds->out);
			fds->out = open((*arg)->content, O_CREAT | O_WRONLY | O_TRUNC, 00777);
		}
		else if (!ft_strcmp((*arg)->content, ">>"))
		{
			(*arg) = (*arg)->next;
			close(fds->out);
			fds->out = open((*arg)->content, O_APPEND | O_CREAT | O_WRONLY, 00777);
		}
		else
		{
			str = ft_strjoin(str, (*arg)->content);
			str = ft_strjoin(str, " ");
		}
		(*arg) = (*arg)->next;
	}
	if (*str == '\0')
		return (printf("command not found\n"), g_exit_code = 127, free(str));
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	execute_redir(tmp, env, fds, str);
	unlink("tmp");
}

void	execute_redir(t_lexer *arg, t_env **env, t_fds *fds, char *str)
{
	char	**cmd;
	char	**envp;
	int		tmp_in;
	int		tmp_out;

	cmd = ft_split(str, ' ');
	if (fds->in < 0 || fds->out < 0)
		return (g_exit_code = 1, printf("fd rerror\n"), free(str));
	tmp_in = dup(0);
	tmp_out = dup(1);
	dup2(fds->in, STDIN_FILENO);
	dup2(fds->out, STDOUT_FILENO);
	close(fds->in);
	close(fds->out);
	if (check_type(cmd[0]))
		builting(env, arg);
	else
	{
		var.cpid = fork();
		var.id += 1;
		if (var.cpid < 0)
			return (g_exit_code = 1, ft_putendl_fd("fork error\n", 2));
		if (var.cpid == 0)
		{
			if (get_path(cmd[0]) == NULL)
				return (g_exit_code = 127, printf("command not found\n"), exit(127));
			envp = env_str(*env);
			execve(get_path(cmd[0]), cmd, envp);
		}
		waitpid(var.cpid, NULL, 0);
	}
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
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
	j = 0;
	while (arg && j < i)
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
		j++;
	}
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
}