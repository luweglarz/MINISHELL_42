/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:48 by user42            #+#    #+#             */
/*   Updated: 2021/07/13 16:58:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(t_cmd cmd)
{
	int size;

	size = 0;
	while (cmd.arg[size])
		size++;
	if (size > 2)
	{
		write(2, "Too much arguments\n", 19);
		return ;
	}
	if (ft_str_isdigit(cmd.arg[1]) == 0)
	{
		write(2, "Not a number\n", 14);
		return ;
	}
	printf("%s\n", cmd.builtin);
	exit(ft_atoi(cmd.arg[1]));
}