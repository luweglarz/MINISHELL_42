/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:29:59 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 16:23:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_in(int i, t_cmd *cmd, char **env_list, int fd)
{
	pid_t 	pid;

	pid = fork();
	if (pid < 0)
		error_errno(cmd, errno);
	if (pid == 0)
	{
		dup2(fd, 1);
		do_builtin(cmd[i], env_list, false);
	}
	return (i + 2);
}
//O_APPEND permission pour append avec >> open
int	do_flows(int i, t_cmd *cmd, char **env_list)
{
	int fd;
	
	while (cmd[i].flows != NULL)
	{
		fd = open(cmd[i + 1].builtin, O_RDWR|O_CREAT, 0664);
		if (ft_strncmp(cmd[i].flows, ">", 2) == 0)
			i = redirect_in(i, cmd, env_list, fd);
		else if (ft_strncmp(cmd[i].flows, ">>", 2) == 0)
			i = redirect_in(i, cmd, env_list, fd);
		i++;
	}
	return (i);
}

void	parse_cmd_array(t_cmd *cmd, char **env_list, int nb_cmd)
{
	int		i;
	int		nb_pipe;

	i = 0;
	while (i < nb_cmd)
	{
		nb_pipe = 0;
		if (cmd[i].pipe == true)
		{
			while (cmd[i + nb_pipe].pipe == true)
				nb_pipe++;
			if (nb_pipe == 1)
				i = single_pipe(i, cmd, env_list);
			else if (nb_pipe > 1)
				i = multi_pipe(i, cmd, env_list, nb_pipe);
			if (i >= nb_cmd)
				break;
		}
		//else if (cmd[i].flows != NULL)
		//	do_flows(i, cmd, env_list);
		//if (i >= nb_cmd)
		//		break;
		do_builtin(cmd[i], env_list, false);
		i++;	
	}
}
