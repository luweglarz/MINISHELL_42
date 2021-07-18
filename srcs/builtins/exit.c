/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:48 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 05:05:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(t_cmd cmd)
{
	int	size;

	size = 0;
	while (cmd.arg[size])
		size++;
	if (size > 2)
	{
		error_errno(&cmd, E2BIG, false);
		return ;
	}
	if (ft_str_isdigit(cmd.arg[1]) == 0)
	{
		error_errno(&cmd, ENOEXEC, false);
		return ;
	}
	printf("%s\n", cmd.builtin);
	exit(ft_atoi(cmd.arg[1]));
}
