/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:24 by user42            #+#    #+#             */
/*   Updated: 2021/08/09 16:23:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(int i, t_cmd *cmd, char **env_list, bool pipe)
{
	int	env_index;

	env_index = 0;
	while (env_list[env_index])
	{
		if (ft_strclen(env_list[env_index], '=') != -1)
		{
			write(cmd[i].fdout, env_list[env_index],
				ft_strlen(env_list[env_index]));
			write(cmd[i].fdout, "\n", 1);
		}
		env_index++;
	}
	if (pipe == true)
		exit(1);
}
