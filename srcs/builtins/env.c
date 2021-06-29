/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:57:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/29 12:21:12 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		builtin_env(t_cmd cmd, char **env_list)
{
	int i;

	i = 0;
	(void)cmd;
	while (env_list[i])
	{
		printf("%s\n", env_list[i]);
		i++;
	}
}
