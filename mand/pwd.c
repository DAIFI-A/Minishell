/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:59:39 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/05 14:53:37 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"../minishell.h"

void	pwd_env(char **str, t_env *env)
{
	int		i;
	char	cwd[1024];

	i = 0;
	while (str[i])
		i++;
	if (i > 1)
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