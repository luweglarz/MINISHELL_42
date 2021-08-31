/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:54:32 by ugtheven          #+#    #+#             */
/*   Updated: 2021/08/31 19:13:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	envdup(char **env_list, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		env_list[i] = ft_strdup(tmp[i]);
		i++;
	}
	env_list[i] = NULL;
}

void	envdup_plus(char **env_list, char **tmp, char *plus)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		env_list[i] = ft_strdup(tmp[i]);
		i++;
	}
	env_list[i] = ft_strdup(plus);
	i++;
	env_list[i] = NULL;
}

void	envdup_n_change(char **tmp, char **env_list, char *change, int exist)
{
	int	i;

	i = 0;
	while (i < exist)
	{
		tmp[i] = ft_strdup(env_list[i]);
		i++;
	}
	tmp[i] = ft_strdup(change);
	i++;
	while (env_list[i])
	{
		tmp[i] = ft_strdup(env_list[i]);
		i++;
	}
	tmp[i] = NULL;
}

void	envdup_without(char **env_list, char **tmp, int without)
{
	int	i;

	i = 0;
	while (i < without)
	{
		tmp[i] = ft_strdup(env_list[i]);
		i++;
	}
	while (env_list[i + 1])
	{
		tmp[i] = ft_strdup(env_list[i + 1]);
		i++;
	}
	tmp[i] = NULL;
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
