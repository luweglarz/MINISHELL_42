/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:04:02 by user42            #+#    #+#             */
/*   Updated: 2021/07/20 19:13:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_pars
{
	char	*var_content;
	char	*var_name;
	char	*tmp;
	char	*res;
	int		index;
	int		stop;
	int		inquote;
	int		i;
	int		j;
}				t_pars;

void	close_command(int *cmd_started, int *nb_cmd);
int		count_command(const char *line, int i, int len, int	inquote);
int		parse_command(const char *line);
int		count_arg(t_cmd cmd);

int		quote_inside(t_cmd *cmd, int i, int j);
void	get_quote_content(char *tmp, int *i, int *res_index, char *res);
char	*arg_without_quote(char *tmp, t_cmd *cmd, int ind, int ind2);
void	del_quotes(t_cmd *cmd, int nb_cmd);

int		check_inquote(int c, int inquote);
int		check_solo_quote(char *arg, int inquote);
int		check_quote(char *arg, int i, char c);
int		check_unused(const char *line);
int		check_space_unused(const char *line, int i, int redirection);

int		check_sep(const char *line);
int		check_redirection_input(const char *line, int i);
int		check_redirection_output(const char *line, int i);
int		check_redirection(const char *line);
int		not_only_space(const char *line);

int		dollar_inside(t_cmd *cmd, int i, int j);
char	*ft_getenv_splited(char *var_name, char **env_list);
void	get_exit_code(t_pars *pars);
void	init_struct(t_pars *pars, int i, int j);

void	fill_tmp(t_cmd *cmd, t_pars *pars);
void	fill_before_return(t_cmd *cmd, t_pars *pars);
void	get_dollar(t_cmd *cmd, t_pars *pars);
void	get_var_content(t_cmd *cmd, t_pars *pars, char **env_list);

void	treat_dollar(t_cmd *cmd, t_pars *pars, char **env_list);
void	expand_env_arg(t_cmd *cmd, char **env_list, int i, int j);
void	format_args(t_cmd *cmd, char **env_list, int nb_cmd);

#endif
