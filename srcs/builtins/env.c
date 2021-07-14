/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:24 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 02:50:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_cmd cmd, char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i])
	{
		write(cmd.fdout, env_list[i], ft_strlen(env_list[i]));
		write(cmd.fdout, "\n", 1);
		i++;
	}
}
