/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/28 14:52:35 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		execpath(t_cmd cmd, char **env_list, bool pipe)
{
	pid_t 		pid;
	
	if (pipe == false)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			execve(cmd.builtin, cmd.arg, env_list);
			error(&cmd, errno);
		}
		waitpid(pid, NULL, 0);
	}
	else if (pipe == true)
	{
		execve(cmd.builtin, cmd.arg, env_list);
		error(&cmd, errno);
	}
}