/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:59:39 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/09 16:30:11 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../mini.h"

void	pwd_env(t_lexer *arg)
{
	char	cwd[1024];

	if (arg->next != NULL && ft_strcmp(arg->next->content, ">"))
	{
		g_exit_code = 1;
		ft_putendl_fd("pwd: too many arguments", 2);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	else
	{
		g_exit_code = 1;
		ft_putendl_fd("Unable to get working directory", 2);
	}
}