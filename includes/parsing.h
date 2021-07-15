/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:04:02 by user42            #+#    #+#             */
/*   Updated: 2021/07/15 03:34:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_pars
{
	char *var_content;
	char *var_name;
	char *tmp;
	char *res;
	int index;
	int stop;
	int inquote;
}				t_pars;

void	close_command(int *cmd_started, int *nb_cmd);
int		count_command(const char *line, int i, int len, int	inquote);
int		parse_command(const char *line);
int		count_arg(t_cmd cmd);

//char	*format_env(const char *line, char **env_list);

int		check_inquote(int c, int inquote);
int		check_sep(const char *line);
int		check_unclosed(const char *line);
int		check_redirection_input(const char *line, int i);
int		check_redirection_output(const char *line, int i);
int		check_redirection(const char *line);
int		check_space_unused(const char *line, int i, int redirection);
int		check_unused(const char *line);
int		not_only_space(const char *line);
void	init_env_parse(t_pars *pars);

#endif
