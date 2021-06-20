/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/20 21:53:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		execpath(t_cmd cmd, char **env_list)
{
	int			fds[2];
	__pid_t 	pid;

	if (pipe(fds) != 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (!cmd.arg[0])
			cmd.arg[0] = ft_strchr(cmd.builtin, '/');
			printf("cmd arg %s\n", cmd.arg[0]);
	}
	wait(NULL);
	
}