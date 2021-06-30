/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:52:22 by ugtheven          #+#    #+#             */
/*   Updated: 2021/06/30 18:52:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

char	**get_env_names(char **env_list);
int		var_exist(t_cmd cmd, char **env_list);
int		var_already_exist(t_cmd cmd, char **env_list);

void	add_env_var(char **env_list, int len, char *add);
void	change_env_var(char **env_list, int len, int exist, char *change);
void	del_env_var(char **env_list, int len, int to_del);

int		nb_env(char **env_list);
void	free_env(int nb_env, char **env_list);
void	free_env_list(int nb_env, char **env_list);

void	envdup(char **env_list, char **tmp);
void	envdup_n_change(char **tmp, char **env_list, char *change, int exist);
void	envdup_plus(char **env_list, char **tmp, char *plus);
void	envdup_without(char **env_list, char **tmp, int without);

#endif