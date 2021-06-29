/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:21:19 by user42            #+#    #+#             */
/*   Updated: 2021/06/29 12:20:59 by ugtheven         ###   ########.fr       */
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

char	**envdup(int nb_env, char **env_list)
{
	char **tmp;
	int i;

	tmp = malloc(sizeof(char *) * (nb_env + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (env_list[i])
	{
		tmp[i] = ft_strdup(env_list[i]);
		i++;
	}
	env_list[i] = NULL;
	return (tmp);
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
