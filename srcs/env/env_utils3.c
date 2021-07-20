/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 02:48:05 by user42            #+#    #+#             */
/*   Updated: 2021/07/20 20:08:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_var(char **env_list, int len, char *add)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * len + 2);
	envdup_plus(tmp, env_list, add);
	free_env_list(len, env_list);
	*env_list = malloc(sizeof(char *) * len + 2);
	envdup(env_list, tmp);
	//free_env(len, tmp);
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

void	display_env(t_cmd cmd, char **var_names, char **var_contents)
{
	int	i;

	i = 0;
	while (var_names[i])
	{
		write(cmd.fdout, "declare -x ", 11);
		write(cmd.fdout, var_names[i], ft_strlen(var_names[i]));
		write(cmd.fdout, "=\"", 2);
		write(cmd.fdout, var_contents[i], ft_strlen(var_names[i]));
		write(cmd.fdout, "\"\n", 2);
		i++;
	}
}

void	swap_env(char **content1, char **content2, char **name1, char **name2)
{
	char	*save;

	save = *content1;
	*content1 = *content2;
	*content2 = save;
	save = *name1;
	*name1 = *name2;
	*name2 = save;
}
