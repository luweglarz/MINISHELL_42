/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:55:54 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 13:06:33 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_arg(t_cmd cmd)
{
	int	i;

	i = 0;
	while (cmd.arg[i])
		i++;
	return (i);
}

int	var_already_exist(t_cmd cmd, char **env_list)
{
	int		i;
	char	**env_names;
	char	*tmp;

	i = 0;
	if (count_arg(cmd) > 1)
		return (-2);
	else if (count_arg(cmd) == 1)
	{
		if (ft_strclen(cmd.arg[0], '=') == -1)
			return (-3);
		tmp = ft_substr(cmd.arg[0], 0, ft_strclen(cmd.arg[0], '='));
		env_names = get_env_names(env_list);
		while (env_names[i])
		{
			if (ft_strcmp(tmp, env_names[i]) == 0)
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

void	add_env_var(char **env_list, int len, char *add)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * len + 2);
	envdup_plus(tmp, env_list, add);
	free_env_list(len, env_list);
	*env_list = malloc(sizeof(char *) * len + 2);
	envdup(env_list, tmp);
	free_env(len, tmp);
}

void	change_env_var(char **env_list, int len, int exist, char *change)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * len + 1);
	envdup_n_change(tmp, env_list, change, exist);
	free_env_list(len, env_list);
	*env_list = malloc(sizeof(char *) * len + 1);
	envdup(env_list, tmp);
	free_env(len, tmp);
}

void	builtin_export(t_cmd cmd, char **env_list)
{
	char	**tmp;
	int		exist;
	int		i;
	int		len;

	i = 0;
	tmp = NULL;
	exist = var_already_exist(cmd, env_list);
	len = nb_env(env_list);
	if (exist > 0)
		change_env_var(env_list, len, exist, cmd.arg[0]);
	else if (exist == -1)
		add_env_var(env_list, len, cmd.arg[0]);
	else if (exist == -2)
		printf("La fonction \"export\" ne peut prendre qu'un parametre.\n");
	else if (exist == -3)
		printf("Mauvais format pour la fonction \"export\".\n");
}
