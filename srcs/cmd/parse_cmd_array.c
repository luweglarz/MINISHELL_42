/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:29:59 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 14:48:49 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			dprintf(STDERR_FILENO, "bonjour\n");
			while (cmd[i + nb_pipe].pipe == true)
				nb_pipe++;
			if (nb_pipe == 1 && cmd[i + 1].builtin != NULL)
			{
				printf("test\n");
				i = single_pipe(i, cmd, env_list);
			}
			else if (nb_pipe > 1)
				i = multi_pipe(i, cmd, env_list, nb_pipe);
			if (i >= nb_cmd)
				break ;
		}
		do_builtin(cmd[i], env_list, false);
		i++;
	}
}
