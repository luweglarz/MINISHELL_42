/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/25 22:59:04 by user42           ###   ########.fr       */
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
			printf("test1\n");
			error(&cmd, errno);
		}
		printf("erro %d\n", errno);
		waitpid(pid, NULL, 0);
		printf("2test\n");
	}
	else if (pipe == true)
	{
		execve(cmd.builtin, cmd.arg, env_list);
		error(&cmd, errno);
	}
}