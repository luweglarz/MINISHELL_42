/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:55:54 by user42            #+#    #+#             */
/*   Updated: 2021/07/13 17:22:01 by user42           ###   ########.fr       */
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

void	display_env(t_cmd cmd, char **tmp)
{
	int i;
	
	i = 0;
	while (tmp[i])
	{
		write(cmd.fdout,  tmp[i], ft_strlen(tmp[i]));
		write(cmd.fdout, "\n", 1);
		i++;
	}
}

void	swap_env(char **s1, char **s2, char **name1, char **name2)
{
	char *save;

	save = *s1;
	*s1 = *s2;
	*s2 = save;
	save = *name1;
	*name1 = *name2;
	*name2 = save;
}

void	display_env_ascii(t_cmd cmd, char **env_list)
{
	char **tmp;
	char **var_names;
	int i;
	int j;

	i = 0;
	var_names = get_env_names(env_list);
	tmp = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	envdup(tmp, env_list);
	while (tmp[i])
	{
		j = i + 1;
		while (tmp[j])
		{
			if (ft_strcmp(var_names[i], var_names[j]) > 0)
				swap_env(&tmp[i], &tmp[j], &var_names[i], &var_names[j]);
			j++;
		}
		i++;
	}
	display_env(cmd, tmp);
	free_env(nb_env(tmp), tmp);
	free_env(nb_env(var_names), var_names);
}

void	builtin_export(t_cmd cmd, char **env_list)
{
	int		exist;
	int		i;

	i = 0;
	if (count_arg(cmd) > 1)
	{
		exist = var_already_exist(cmd, env_list);
		if (exist > 0)
			change_env_var(env_list, nb_env(env_list), exist, cmd.arg[1]);
		else if (exist == -1)
			add_env_var(env_list, nb_env(env_list), cmd.arg[1]);
		else if (exist == -2)
			printf("Mauvais format pour la fonction \"export\".\n");
	}
	else if (count_arg(cmd) == 1)
		display_env_ascii(cmd, env_list);
	else
		printf("Pas assez d'arguments pour la fonction \"export\".\n");
}
