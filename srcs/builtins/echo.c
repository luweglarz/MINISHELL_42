/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:17:20 by user42            #+#    #+#             */
/*   Updated: 2021/06/17 17:35:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_cmd cmd)
{
	if (cmd.pipe == true)
	{
		
		return ;
	}
	if (cmd.option && ft_strncmp(cmd.option, "-n", 2) == 0)
		printf("%s",cmd.arg);
	else if (cmd.error == false)
		printf("%s\n", cmd.arg);
}