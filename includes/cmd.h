/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:01:42 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 13:16:55 by ugtheven         ###   ########.fr       */
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
	char	**list;
	char	***token;
}				t_env_l;

void		parse_cmd_array(t_cmd *cmd, t_env_l *env, int nb_cmd);
void		exec_builtin(int i, t_cmd *cmd, t_env_l *env, bool pipe);

#endif