/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:24 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 14:38:39 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(int i, t_cmd *cmd, t_env_l *env, bool pipe)
{
	int	env_index;

	env_index = 0;
	if (count_arg(cmd[i]) > 1)
		g_err = 1;
	else
		g_err = 0;
	while (env->list[env_index])
	{
		if (ft_strclen(env->list[env_index], '=') != -1)
		{
			write(cmd[i].fdout, env->list[env_index],
				ft_strlen(env->list[env_index]));
			write(cmd[i].fdout, "\n", 1);
		}
		int j = 0;
		while (env->token[env_index][j])
		{
			printf("	token[%d]=%s\n", j, env->token[env_index][j]);
			j++;
		}
		env_index++;
	}
	if (pipe == true)
		exit(1);
}
