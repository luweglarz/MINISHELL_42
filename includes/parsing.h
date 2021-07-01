/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:04:02 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 12:59:19 by ugtheven         ###   ########.fr       */
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
}				t_pars;

void	close_command(int *cmd_started, int *nb_cmd);
int		count_command(const char *line, int i);
int		parse_command(const char *line);

char	*replace_env_var(const char *line, char **env_list, int i, int stop);
char	*del_dollar(const char *line, char quote);
char	*expand_var_content(const char *line, int *index, char **env_list, int i, int space);
char	*strdup_without_space(char *tmp);
char	*get_var_name(const char *line, int *index);

int		check_inquote(const char *line, int i, int inquote);
int		check_sep(const char *line);
int		not_only_space(const char *line);
void	init_env_parse(t_pars *pars);

#endif
