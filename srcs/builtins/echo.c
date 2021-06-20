/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:17:20 by user42            #+#    #+#             */
/*   Updated: 2021/06/17 19:41:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_cmd cmd)
{
	int		i;

	i = 0;
	if (cmd.option && ft_strncmp(cmd.option, "-n", 2) == 0)
	{
		while (cmd.arg[i])
		{
			printf("%s",cmd.arg[i]);
			i++;
		}
	}
	else if (cmd.error == false)
	{
		while (cmd.arg[i])
		{
			printf("%s", cmd.arg[i]);
			i++;
		}
		printf("\n");
	}
}