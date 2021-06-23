/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/23 15:58:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		execpath(t_cmd cmd, char **env_list)
{
	pid_t 		pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (!cmd.arg[0])
			cmd.arg[0] = ft_strschr(cmd.builtin, '/', 1);
		execve(cmd.builtin, &cmd.arg[0], env_list);
		exit(-1); // si on arrive ici c'est que execve ne c'est pas executer correctement donc il faudra free etc
	}
	waitpid(pid, NULL, 0);
}