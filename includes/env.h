/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 21:35:16 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 14:34:00 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

char	**get_env_content(char **env_list);
void	init_token(t_env_l *env);

char	**get_env_names(char **env_list);
int		var_exist(t_cmd cmd, int w_arg, char **env_list);
int		var_already_exist(t_cmd cmd, char **env_list, int a_i, int i);

void	add_env_var(t_env_l *env, int len, char *add);
void	change_env_var(t_env_l *env, int len, int exist, char *change);
void	del_env_var(t_env_l *env, int len, int to_del);

int		nb_env(char **env_list);
void	free_env(int nb_env, char **env_list);
void	free_env_list(int nb_env, char **env_list);
char	**init_env(char **envp, int ac, char **av);
char	*ft_getenv(char *var_name, char **env_list);

void	envdup(char **env_list, char **tmp);
void	envdup_n_change(char **tmp, char **env_list, char *change, int exist);
void	envdup_plus(char **env_list, char **tmp, char *plus);
void	envdup_without(char **env_list, char **tmp, int without);

void	display_env(t_cmd cmd, char **var_names,
			char **var_contents, t_env_l *env);
void	swap_env(char **content1, char **content2, char **name1, char **name2);

#endif