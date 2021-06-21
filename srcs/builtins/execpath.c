/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/21 14:12:02 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		execpath(t_cmd cmd, char **env_list)
{
	int			fds[2];
	pid_t 		pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (!cmd.arg[0])
			cmd.arg[0] = ft_strchr(cmd.builtin, '/');
			printf("cmd arg %s\n", cmd.arg[0]);
		execve(cmd.builtin, &cmd.arg[0], env_list);
	}
	wait(NULL);
}