/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:04:02 by user42            #+#    #+#             */
/*   Updated: 2021/07/07 12:26:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_pars
{
		char	*res;
		char	*tmp;
		char	*tmp2;
		char	*expanded;
		int		inquote;
		int		stop;
}				t_pars;

void	close_command(int *cmd_started, int *nb_cmd);
int		count_command(const char *line, int i);
int		parse_command(const char *line);
int		count_arg(t_cmd cmd);

char	*replace_env_var(const char *line, char **env_list, int i);
char	*del_dollar(const char *line, char quote);
char	*expand_var_content(const char *line, int *index, char **env_list, int i, int space);
char	*strdup_without_space(char *tmp);
char	*get_var_name(const char *line, int *index);

int		check_inquote(int c, int inquote);
int		check_sep(const char *line);
int		not_only_space(const char *line);
void	init_env_parse(t_pars *pars);

#endif
