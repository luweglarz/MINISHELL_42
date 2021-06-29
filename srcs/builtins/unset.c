/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:56:37 by user42            #+#    #+#             */
/*   Updated: 2021/06/30 00:49:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strclen(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	if (str[i] == (char)c)
		return (i);
	return (-1);
}

char	**get_env_names(char **env_list)
{
	int i;
	char **env_names;

	i = 0;
	env_names = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	while (env_list[i])
	{
		env_names[i] = ft_substr(env_list[i], 0, ft_strclen(env_list[i], '='));
		i++;
	}
	env_names[i] = NULL;
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
				free_env(nb_env(env_names), env_names);
				return (i);
			}
			i++;
		}
		free_env(nb_env(env_names), env_names);
	}
	return (-1);
}

void		builtin_unset(t_cmd cmd, char **env_list)
{
	char **tmp;
	int	to_del;
	int i;

	i = 0;
	to_del = var_exist(cmd, env_list);
	if (to_del > 0)
	{
		tmp = malloc(sizeof(char *) * (nb_env(env_list)));
		while (i < to_del)
		{
			tmp[i] = ft_strdup(env_list[i]);
			i++;
		}
		printf("La ligne a delete est : %s\n", env_list[i]);
		while (env_list[i + 1])
		{
			tmp[i] = ft_strdup(env_list[i + 1]);
			i++;
		}
		tmp[i] = NULL;
		i = 0;
		while (env_list[i])
		{
			if (env_list[i])
			{
				free(env_list[i]);
				env_list[i] = NULL;
			}
			i++;
		}
		free(env_list);
		i = 0;
		while (i < nb_env(tmp))
		{
			env_list[i] = ft_strdup(tmp[i]);
			i++;
		}
		env_list[i] = NULL;
		i = 0;
		while (tmp[i])
		{
			if (tmp[i])
			{
				free(tmp[i]);
				tmp[i] = NULL;
			}
			i++;
		}
		free(tmp);
	}
	else if (to_del == -2)
		printf("La fonction \"env\" ne peut prendre qu'un parametre.\n");
}