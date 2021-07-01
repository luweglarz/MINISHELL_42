/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:48 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 12:14:15 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		builtin_exit(t_cmd cmd)
{
	// cas particulié quand on envoi des char etc
	int size;

	size = 0;
	while (cmd.arg[size])
		size++;
	if (size > 2)
	{
		write(2, "Too much arguments\n", 19);
		return ;
	}
	printf("%s\n", cmd.builtin);
	exit(ft_atoi(cmd.arg[1]));
}