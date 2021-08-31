/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:04:02 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 19:03:54 by user42           ###   ########.fr       */
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

char	*name_to_tokens(char *line, int *i, t_env_l *env);
char	*name_to_value(char *line, int *i, char **env_list);
void	get_front_buffer(t_pars *exp, char *line);
void	get_median_buffer(t_pars *exp, char *line);
void	get_back_buffer(t_pars *exp, char *line);

void	init_exp(t_pars *exp);
void	add_expanded(t_pars *exp, char *line);
void	treat_dollar(t_pars *exp, char *line, t_env_l *env);
char	*expand_env_value(t_pars *exp, char *line, t_env_l *env);

void	close_command(int *cmd_started, int *nb_cmd);
int		count_command(const char *line, int i, int len, int	inquote);
int		parse_command(const char *line);
int		count_arg(t_cmd cmd);

char	*remove_quotes(char *expanded);
void	content_without_quote(char *expanded,
			int *i, int *res_index, char *res);

int		nb_quote(char *expanded);
int		increment_nbquote(char *expanded, int *i);
void	update_inquote(char *tmp, int *inquote, int *i, char c);
void	fill_other_char(char *res, int *res_index, char *tmp, int *i);

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

void	fill_other_char(char *res, int *res_index, char *tmp, int *i);
void	update_inquote(char *tmp, int *inquote, int *i, char c);
void	treat_quotes(int i, int inquote, char *tmp, char *res);
char	*arg_without_quote(char *tmp, t_cmd *cmd, int ind, int ind2);

#endif
