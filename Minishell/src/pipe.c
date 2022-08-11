/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:38:47 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/11 17:09:00 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../mini.h"

void	content_handler(t_lexer **arg)
{
	int		fd;
	int		fd1;
	char	*str;

	while ((*arg) && ft_strcmp((*arg)->content, "|"))
	{
		if (!ft_strcmp((*arg)->content, ">"))
			fd = open((*arg)->next->content, O_CREAT | O_WRONLY, 0777);
		else if (!ft_strcmp((*arg)->content, "<"))
			fd1 = open((*arg)->next->content, O_CREAT | O_RDONLY, 0777);
		else
		{
			str = ft_strdup((*arg)->content);
			while (*arg &&ft_strcmp((*arg)->content, "|"))
			{
				(*arg) = (*arg)->next;
				str = ft_strjoin(str, " ");
				str = ft_strjoin(str, (*arg)->content);
			}
		}
	}
	puts(str);
}

// char	*parse_input(t_lexer	*arg)
// {
// 	char	*str;
// 	char	**cmd;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	str = ft_strdup(arg->content)
// 	while (arg)
// 	{
// 		arg = arg->next;
// 		str = ft_strjoin(str, " ");
// 		str = ft_strjoin(str, arg->content);
// 	}
// 	cmd = ft_split(str, '|');
// 	while (cmd[i])
// 	{
// 		j = 0;
// 		while (cmd[i][j])
// 		{
// 			if (!ft_strcmp((*arg)->content, ">"))
				
// 		}
// 	}
// }

void	execute_pipe(t_env *env, t_lexer *arg, int i, char **envp)
{
	int		number_pipe;
	int		*fd;
	//pid_t	cpid;
	int		j;

	(void)envp;
	(void)env;
	number_pipe = i * 2;
	j = 0;
	fd = (int *)malloc(sizeof(number_pipe));
	content_handler(&arg);
}