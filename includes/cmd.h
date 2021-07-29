/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:01:42 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 21:48:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

typedef struct s_cmd
{
	char			*builtin;
	char			**arg;
	bool			pipe;
	int				fdout;
	int				fdin;
}				t_cmd;

void		parse_cmd_array(t_cmd *cmd, char **env_list, int nb_cmd);
void		exec_builtin(int i, t_cmd *cmd, char **env_list, bool pipe);

#endif