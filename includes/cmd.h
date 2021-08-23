/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:01:42 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 18:36:53 by user42           ###   ########.fr       */
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

typedef struct s_env_l
{
	char **list;
}				t_env_l;

void		parse_cmd_array(t_cmd *cmd, t_env_l *env, int nb_cmd);
void		exec_builtin(int i, t_cmd *cmd, t_env_l *env, bool pipe);

#endif