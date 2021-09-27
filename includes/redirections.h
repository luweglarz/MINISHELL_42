/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 21:07:03 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 19:05:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

int	pass_brackets(const char *line,
		int j, int *start, int *doublebracket);
int	size_with_redirection(const char *line, int i);

int	bracket_out_in(const char *line, int j, t_cmd *cmd, t_env_l *env);
int	bracket_out(const char *line, int j, t_cmd *cmd);
int	bracket_in(const char *line, int j, t_cmd *cmd, t_env_l *env);

int	single_pipe(int i, t_cmd *cmd, t_env_l *env);
int	multi_pipe(int i, t_cmd *cmd, t_env_l *env, int nb_pipe);

int	wait_forks(pid_t *pid, int nb_pipe);

#endif