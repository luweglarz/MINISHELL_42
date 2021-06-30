/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:56:37 by user42            #+#    #+#             */
/*   Updated: 2021/06/30 15:52:25 by ugtheven         ###   ########.fr       */
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
	if (i > 1)
		return (-2);
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

void	del_env_var(char **env_list, int len, int to_del)
{
	char **tmp;

	tmp = malloc(sizeof(char *) * len);
	envdup_without(env_list, tmp, to_del);
	free_env_list(len, env_list);
	*env_list = malloc(sizeof(char *) * len);
	envdup(env_list, tmp);
	free_env(len - 1, tmp);
}

void		builtin_unset(t_cmd cmd, char **env_list)
{
	int	to_del;
	int i;
	int len;

	i = 0;
	to_del = var_exist(cmd, env_list);
	len = nb_env(env_list);
	if (to_del > 0)
		del_env_var(env_list, len, to_del);
	else if (to_del == -2)
		printf("La fonction \"env\" ne peut prendre qu'un parametre.\n");
}