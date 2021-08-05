/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 21:07:03 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 21:19:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

int	pass_brackets(const char *line,
		int j, int *start, int *doublebracket);
int	size_with_redirection(const char *line, int i);

int	bracket_out_in(const char *line, int j, t_cmd *cmd);
int	bracket_out(const char *line, int j, t_cmd *cmd);
int	bracket_in(const char *line, int j, t_cmd *cmd);

int	single_pipe(int i, t_cmd *cmd, char **env_list);
int	multi_pipe(int i, t_cmd *cmd, char **env_list, int nb_pipe);

#endif