/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:28:11 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/15 17:11:44 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	ft_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
}

void	ft_exit(char *str)
{
	int	i;
	int num = 0;

	i = 0;
	while(str[i])
	{
		if (ft_isdigit(str[i]) == 1)
		{
			printf("Exit\n");
			ft_putendl_fd("Error: numeric arg required", 2);
			exit(255);
		}
		i++;
	}
	if (str != NULL)
		num = ft_atoi(str);
	printf("Exit\n");
	exit(num);
}

void	ft_export(t_env **env, char *content)
{
	t_env	*tmp;
	t_env	*top;
	char	**tab;
	int		i;

	tmp = *env;
	top = *env;
	if (content)
	{
		tab = ft_split(content, '=');
		if (tab[0])
		{
			if (tab[1])
				ft_lstadd_back_env(env, ft_lstnew_env(tab[0], tab[1], 1));
			else
				ft_lstadd_back_env(env, ft_lstnew_env(tab[0], NULL, 0));
		}
		free(tab);
		return ;
	}
	while (top)
	{
		i = 0;
		*env = tmp;
		while (*env)
		{
			if (ft_strcmp(top->name, (*env)->name) > 0)
				i++;
			*env = (*env)->next;
		}
		top->index = i;
		top = top->next;
	}
	*env = tmp;
	top = tmp;
	i = 0;
	while (top)
	{
		*env = tmp;
		while (*env)
		{
			if ((*env)->index == i)
			{
				if (!(*env)->value)
					printf("declare -x %s\n", (*env)->name);
				else
					printf("declare -x %s=\"%s\"\n", (*env)->name, (*env)->value);
				i++;
				break ;
			}
			*env = (*env)->next;
		}
		top = top->next;
	}
	*env = tmp;
}