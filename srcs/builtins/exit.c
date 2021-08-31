/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:48 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 18:41:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(int i, t_cmd *cmd, bool pipe, t_env_l *env)
{
	int	size;

	size = 0;
	while (cmd[i].arg[size])
		size++;
	if (size == 1)
		exit_free_env(env, 0);
	if (size > 2)
	{
		error_errno(cmd, E2BIG, false, env);
		return ;
	}
	if (ft_str_isdigit(cmd[i].arg[1]) == 0)
	{
		error_errno(cmd, ENOEXEC, false, env);
		return ;
	}
	if (pipe == false)
		printf("%s\n", cmd[i].builtin);
	if (cmd[i].arg[1][0] == '-')
		exit_free_env(env, 255 - (ft_atoi(cmd[i].arg[1]) * -1) + 1);
	else
		exit_free_env(env, ft_atoi(cmd[i].arg[1]));
}
