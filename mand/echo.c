/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:06:02 by adaifi            #+#    #+#             */
/*   Updated: 2022/08/04 16:33:39 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	echo(t_env *env, char **cmd, t_args *arg)
{
	int		i;
	char	*output;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
	{
		printf("\n");
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		if (cmd[1][0] == '-' && cmd[1][1] == 'n')
		{
			output = ft_strdup(cmd[2]);
			i = 3;
			while (cmd[i])
			{
				output = ft_strjoin(output, " ");
				output = ft_strjoin(output, cmd[i]);
				i++;
			}
			printf("%s", output);
		}
		else
		{
			output = ft_strdup(cmd[1]);
			i = 2;
			while (cmd[i])
			{
				output = ft_strjoin(output, " ");
				output = ft_strjoin(output, cmd[i]);
				i++;
			}
			printf("%s\n", output);
		}
	}
	free(output);
}