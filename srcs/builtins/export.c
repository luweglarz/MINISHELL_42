/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:55:54 by user42            #+#    #+#             */
/*   Updated: 2021/07/22 16:51:35 by user42           ###   ########.fr       */
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
	if (count_arg(cmd) > 0)
	{
		if (ft_strclen(cmd.arg[1], '=') == -1)
			return (-2);
		tmp = ft_substr(cmd.arg[1], 0, ft_strclen(cmd.arg[1], '='));
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

char	**get_env_content(char **env_list)
{
	int		i;
	char	**env_names;

	i = 0;
	env_names = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	while (env_list[i])
	{
		env_names[i] = ft_substr(env_list[i],
				ft_strclen(env_list[i], '=') + 1, ft_strlen(env_list[i]));
		i++;
	}
	env_names[i] = NULL;
	return (env_names);
}

void	display_env_ascii(t_cmd cmd, char **env_list)
{
	char	**var_names;
	char	**var_contents;
	int		i;
	int		j;

	i = 0;
	var_names = get_env_names(env_list);
	var_contents = get_env_content(env_list);
	while (env_list[i])
	{
		j = i + 1;
		while (env_list[j])
		{
			if (ft_strcmp(var_names[i], var_names[j]) > 0)
				swap_env(&var_contents[i],
					&var_contents[j], &var_names[i], &var_names[j]);
			j++;
		}
		i++;
	}
	display_env(cmd, var_names, var_contents);
	free_env(nb_env(var_names), var_names);
	free_env(nb_env(var_names), var_contents);
}

void	builtin_export(int i, t_cmd *cmd, char **env_list)
{
	int		exist;

	if (count_arg(cmd[i]) > 1)
	{
		exist = var_already_exist(cmd[i], env_list);
		if (exist > 0)
			change_env_var(env_list, nb_env(env_list), exist, cmd[i].arg[1]);
		else if (exist == -1)
			add_env_var(env_list, nb_env(env_list), cmd[i].arg[1]);
		else if (exist == -2)
			printf("Mauvais format pour la fonction \"export\".\n");
	}
	else if (count_arg(cmd[i]) == 1)
		display_env_ascii(cmd[i], env_list);
	else
		printf("Pas assez d'arguments pour la fonction \"export\".\n");
}
