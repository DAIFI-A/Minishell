/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:28:11 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/14 19:26:19 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=", env->name);
		printf("%s\n", env->value);
		env = env->next;
	}
}

void	ft_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
}

void	ft_exit(char *str)
{
	int num;

	num = ft_atoi(str);
	printf("num= %d\n", num);
	exit(num);
}