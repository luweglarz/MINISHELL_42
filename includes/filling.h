/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:59:22 by user42            #+#    #+#             */
/*   Updated: 2021/09/06 20:29:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLING_H
# define FILLING_H

# include "minishell.h"

void		fill_cmd_array(const char *line, t_cmd *cmd, t_env_l *env);
void		cmd_init(t_cmd *cmd);

int			count_word(const char *str);
int			word_len(const char *s);
int			check_end_quote(const char *s);
const char	*fill_split(const char *s, char **tab);
char		**split_args(char const *s, const char *builtin);

int			check_inquote_args(const char *line, int i, int *inquote);
int			do_beginning_bracket(int *i, const char *line,
				t_cmd *cmd, t_env_l *env);
int			pass_ascii(const char *line, int i);

#endif