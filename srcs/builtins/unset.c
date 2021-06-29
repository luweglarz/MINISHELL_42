/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:56:37 by user42            #+#    #+#             */
/*   Updated: 2021/06/29 12:58:05 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_env_names(char **env_list)
{
	int i;
	char **env_names;

	i = 0;
	env_names = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	while (env_list[i])
	{
		env_names[i] = ft_strdup(ft_strchr(env_list[i], '='));
		i++;
	}
	env_names[i] = NULL;
	//debug
	i = 0;
	while (env_names[i])
	{
		printf("env_names[%d] = %s\n", i, env_names[i]);
		i++;
	}
	return (env_names);
}

int	var_exist(t_cmd cmd, char **env_list)
{
	int i;
	char **env_names;

	i = 0;
	while (cmd.arg[i])
		i++;
	//si on a plus d'un argument -> on sort
	if (i > 1)
		return (-2);
	//si on en a 1 -> on continue
	else if (i == 1)
	{
		env_names = get_env_names(env_list);
		i = 0;
		while (env_names[i])
		{
			if (ft_strcmp(cmd.arg[0], env_names[i]) == 0)
			{
				free_env(nb_env(env_list), env_list);
				return (i);
			}
			i++;
		}
		if (ft_strcmp(cmd.arg[0], env_names[i]) == 0)
		{
			free_env(nb_env(env_list), env_list);
			return (i);
		}
	}
	return (-1);
}

void		builtin_unset(t_cmd cmd, char **env_list)
{
	int	to_del;
	char **tmp;
	int i;

	to_del = var_exist(cmd, env_list);
	i = 0;
	if (to_del > 0)
	{
		tmp = envdup(nb_env(env_list), env_list);
		free_env(nb_env(env_list), env_list);
		env_list = envdup(nb_env(env_list), tmp);
		while (i < to_del)
		{
			i++;
		}
		printf("La ligne a delete est : %s\n", tmp[to_del]);
		printf("La ligne a delete est : %s\n", tmp[i]);
	}
	else if (to_del == -2)
		printf("La fonction \"env\" ne peut prendre qu'un parametre.\n");
}