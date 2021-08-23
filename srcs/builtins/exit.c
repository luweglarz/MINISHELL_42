/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:48 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 16:02:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(int i, t_cmd *cmd, bool pipe, char **env_list)
{
	int	size;
	int ind;

	size = 0;
	ind = 0;
	while (env_list[ind])
	{
		free(env_list[ind]);
		ind++;
	}
	free(env_list);
	while (cmd[i].arg[size])
		size++;
	if (size == 1)
		exit(0);
	if (size > 2)
	{
		error_errno(cmd, E2BIG, false);
		return ;
	}
	if (ft_str_isdigit(cmd[i].arg[1]) == 0)
	{
		error_errno(cmd, ENOEXEC, false);
		return ;
	}
	if (pipe == false)
		printf("%s\n", cmd[i].builtin);
	if (cmd[i].arg[1][0] == '-')
		exit(255 - (ft_atoi(cmd[i].arg[1]) * -1) + 1);
	else
		exit(ft_atoi(cmd[i].arg[1]));
}
