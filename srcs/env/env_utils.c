/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:21:19 by user42            #+#    #+#             */
/*   Updated: 2021/06/30 14:40:47 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nb_env(char **env_list)
{
	int i;

	i = 0;
	while (env_list[i])
		i++;
	return (i);
}

void		free_env(int nb_env, char **env_list)
{
	int i;

	i = 0;
	while (i < nb_env)
	{
		if (env_list[i])
		{
			free(env_list[i]);
			env_list[i] = NULL;
		}
		i++;
	}
	free(env_list);
}

void		free_env_list(int nb_env, char **env_list)
{
	int i;

	i = 0;
	while (i < nb_env)
	{
		if (env_list[i])
		{
			free(env_list[i]);
			env_list[i] = NULL;
		}
		i++;
	}
	free(*env_list);
}
