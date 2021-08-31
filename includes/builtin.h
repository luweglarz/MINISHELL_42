/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:58:19 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 14:21:35 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void		execpath(int index, t_cmd *cmd, char **env_list, bool pipe);
void		execpath_pipe(t_cmd *cmd, int i, char **env_list);
void		builtin_echo(int index, t_cmd *cmd, bool pipe);
void		builtin_cd(int index, t_cmd *cmd, bool pipe);
void		builtin_pwd(int index, t_cmd *cmd, bool pipe);
void		builtin_export(int index, t_cmd *cmd, t_env_l *env, bool pipe);
void		builtin_unset(int index, t_cmd *cmd, t_env_l *env, bool pipe);
void		builtin_env(int index, t_cmd *cmd, t_env_l *env, bool pipe);
void		builtin_exit(int index, t_cmd *cmd, bool pipe, t_env_l *env);

#endif