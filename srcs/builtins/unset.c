/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:56:37 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 21:17:38 by user42           ###   ########.fr       */
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
	g_err = 1;
	return (-1);
}

void	del_env_var(t_env_l *env, int len, int to_del)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * len);
	envdup_without(env->list, tmp, to_del);
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	env->list = malloc(sizeof(char *) * len);
	envdup(env->list, tmp);
	free_env(len, tmp);
}

void	builtin_unset(int i, t_cmd *cmd, t_env_l *env, bool pipe)
{
	int	to_del;
	int	index;
	int	len;

	to_del = 0;
	index = 1;
	len = nb_env(env->list);
	g_err = 0;
	if (count_arg(cmd[i]) > 1)
	{
		while (index < count_arg(cmd[i]))
		{
			to_del = var_exist(cmd[i], index, env->list);
			if (to_del >= 0)
				del_env_var(env, len, to_del);
			else
				g_err = 1;
			index++;
		}
	}
	if (pipe == true)
		exit(1);
}
