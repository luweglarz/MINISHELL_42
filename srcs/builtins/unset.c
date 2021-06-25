/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:56:37 by user42            #+#    #+#             */
/*   Updated: 2021/06/25 17:24:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		builtin_unset(t_cmd cmd, char **env_list)
{
	char **tmp;
	int i;

	i = 0;
	if (cmd.pipe == false)
	{
		tmp = envdup_without(nb_env(env_list), env_list, cmd.arg[0]);
		free_env(nb_env(env_list), env_list);
		env_list = envdup(nb_env(env_list), tmp);
		free_env(nb_env(env_list), tmp);
	}
}