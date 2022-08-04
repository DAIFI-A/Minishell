/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:59:39 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/04 16:30:26 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../minishell.h"

void	pwd_env(t_env *env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	else
	{
		g_exit_code = 1;
		ft_putendl_fd("Unable to get working directory", 2);
	}
}