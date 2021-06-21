/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:01:42 by user42            #+#    #+#             */
/*   Updated: 2021/06/21 13:59:56 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

typedef struct s_cmd
{
		char			*builtin;
		char			**arg;
		char			*option;
		bool			error;
		bool			pipe;
		int				cmd_index;
}				t_cmd;

void		cmd_init(t_cmd *cmd);
void		fill_cmd_array(const char *line, t_cmd *cmd);
void		parse_cmd_array(t_cmd *cmd, char **env_list, int nb_cmd);

#endif