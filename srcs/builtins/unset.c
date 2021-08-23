/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:56:37 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 16:23:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_env_names(char **env_list)
{
	int		i;
	char	**env_names;
	int		stop;

	i = 0;
	env_names = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	while (env_list[i])
	{
		stop = ft_strclen(env_list[i], '=');
		if (stop != -1)
			env_names[i] = ft_substr(env_list[i], 0, stop);
		else
			env_names[i] = ft_substr(env_list[i], 0, ft_strlen(env_list[i]));
		i++;
	}
	env_names[i] = NULL;
	return (env_names);
}

int	var_exist(t_cmd cmd, int w_arg, char **env_list)
{
	int		i;
	char	**env_names;

	i = 0;
	env_names = get_env_names(env_list);
	while (env_names[i])
	{
		if (ft_strcmp(cmd.arg[w_arg], env_names[i]) == 0)
		{
			free_env(nb_env(env_names), env_names);
			return (i);
		}
		i++;
	}
	free_env(nb_env(env_names), env_names);
	return (-1);
}

void	del_env_var(char **env_list, int len, int to_del)
{
	char	**tmp;
	int i;

	i = 0;
	tmp = malloc(sizeof(char *) * len);
	envdup_without(env_list, tmp, to_del);
	//free_env(len, env_list);
	while (env_list[i])
	{
		free(env_list[i]);
		i++;
	}
	free(env_list);
	env_list = malloc(sizeof(char *) * len);
	envdup(env_list, tmp);
	free_env(len, tmp);
}

void	builtin_unset(int i, t_cmd *cmd, char **env_list, bool pipe)
{
	int	to_del;
	int	index;
	int	len;

	to_del = 0;
	index = 1;
	len = nb_env(env_list);
	if (count_arg(cmd[i]) > 1)
	{
		while (index < count_arg(cmd[i]) && to_del >= 0)
		{
			to_del = var_exist(cmd[i], index, env_list);
			if (to_del >= 0)
				del_env_var(env_list, len, to_del);
			index++;
		}
	}
	else
		printf("Pas assez d'arguments pour la fonction \"unset\".\n");
	if (pipe == true)
		exit(1);
}
