/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:58:19 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 22:51:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H


# include "minishell.h"

void		execpath(t_cmd cmd, char **env_list, bool pipe);
void		builtin_echo(t_cmd cmd, bool pipe);
void		builtin_cd(t_cmd cmd, bool pipe);
void		builtin_pwd(t_cmd cmd, bool pipe);
void		builtin_export(t_cmd cmd, char **env_list);
void		builtin_unset(t_cmd cmd, char **env_list);
void		builtin_env(t_cmd cmd, char **env_list);
void		builtin_exit(t_cmd cmd);

#endif