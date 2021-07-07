/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:01:42 by user42            #+#    #+#             */
/*   Updated: 2021/07/07 15:32:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

typedef struct s_cmd
{
		char			*builtin;
		char			**arg;
		bool			error;
		bool			pipe;
		char			*flows;
}				t_cmd;

void		cmd_init(t_cmd *cmd);
void		fill_cmd_array(const char *line, t_cmd *cmd);
void		parse_cmd_array(t_cmd *cmd, char **env_list, int nb_cmd);

int			count_word(const char *str);
int			word_len(const char *s);
const char	*fill_split(const char *s, char **tab);
char		**split_args(char const *s, const char *builtin);

void		do_builtin(t_cmd cmd, char **env_list, bool pipe);

int			single_pipe(int i, t_cmd *cmd, char **env_list);
int			multi_pipe(int i, t_cmd *cmd, char **env_list, int nb_pipe);


#endif