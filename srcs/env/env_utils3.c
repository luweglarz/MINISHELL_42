/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 02:48:05 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 02:50:29 by user42           ###   ########.fr       */
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
	int	i;

	i = 0;
	while (tmp[i])
	{
		write(cmd.fdout, tmp[i], ft_strlen(tmp[i]));
		write(cmd.fdout, "\n", 1);
		i++;
	}
}

void	swap_env(char **s1, char **s2, char **name1, char **name2)
{
	char	*save;

	save = *s1;
	*s1 = *s2;
	*s2 = save;
	save = *name1;
	*name1 = *name2;
	*name2 = save;
}
