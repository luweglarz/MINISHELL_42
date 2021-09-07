/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:04:02 by user42            #+#    #+#             */
/*   Updated: 2021/09/07 19:56:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_pars
{
	char	*newline;
	char	*expanded;
	char	*tmp;
	char	*save;
	int		i;
	int		inquote;
	int		stop;
	int		remember;
}				t_pars;

void	exit_free_env(t_env_l *env, int nb);

void	close_command(int *cmd_started, int *nb_cmd);
int		count_command(const char *line, int i, int len, int inquote);
int		parse_command(const char *line);
int		count_arg(t_cmd cmd);

int		check_inquote(int c, int inquote);
int		check_solo_quote(char *arg, int inquote);
int		check_quote(char *arg, int i, char c);
int		check_unused(const char *line);
int		check_space_unused(const char *line, int i, int redirection);

char	*name_to_tokens(char *line, int *i, t_env_l *env);
char	*name_to_value(char *line, int *i, char **env_list);
void	get_front_buffer(t_pars *exp, char *line);
void	get_median_buffer(t_pars *exp, char *line);
void	get_back_buffer(t_pars *exp, char *line);

void	init_exp(t_pars *exp);
void	add_expanded(t_pars *exp, char *line);
void	treat_dollar(t_pars *exp, char *line, t_env_l *env);
char	*expand_env_value(t_pars *exp, char *line, t_env_l *env);

int		check_sep(const char *line);
int		check_redirection_input(const char *line, int i);
int		check_redirection_output(const char *line, int i);
int		check_redirection(const char *line);
int		not_only_space(const char *line);

void	fill_other_char(char *res, int *res_index, char *tmp, int *i);
void	update_inquote(char *tmp, int *inquote, int *i, char c);
void	treat_quotes(int i, int inquote, char *tmp, char *res);
char	*arg_without_quote(char *tmp, t_cmd *cmd, int ind, int ind2);

int		count_quote(char *expanded, int *i);
int		is_quote_in(char *expanded);
void	start_buffer(char *line, t_pars *qte);
void	get_saved_quote(char *line, t_pars *qte);

void	mid_buffer(char *line, t_pars *qte);
void	end_buffer(char *line, t_pars *qte);
void	add_quotes(char *line, t_pars *qte);
char	*save_quotes(char *line);

void	get_quote_content(char *tmp, int *i, int *res_index, char *res);
void	fill_other_char(char *res, int *res_index, char *tmp, int *i);
void	update_inquote(char *tmp, int *inquote, int *i, char c);
int		increment_quote(t_cmd *cmd, int i, int j, int *index);

int		quote_inside(t_cmd *cmd, int i, int j);
int		is_quote_in(char *expanded);
void	treat_quotes(int i, int inquote, char *tmp, char *res);
char	*arg_without_quote(char *tmp, t_cmd *cmd, int ind, int ind2);
void	del_quotes(t_cmd *cmd, int nb_cmd);

char	*save_quotes(char *line);

#endif
