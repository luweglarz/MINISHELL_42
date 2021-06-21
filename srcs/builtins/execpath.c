/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/21 12:34:31 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		execpath(t_cmd cmd, char **env_list)
{
	int			fds[2];
	pid_t 	pid;

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
			(void)env_list;
	}
	wait(NULL);
	
}