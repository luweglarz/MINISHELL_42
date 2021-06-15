/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:13:53 by lweglarz          #+#    #+#             */
/*   Updated: 2021/06/15 16:52:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_cmd
{
		char			*builtin;
		char			*arg;
		char			*option;
		bool			error;
		int				cmd_index;
}				t_cmd;

size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isascii(int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);

int			parse_line(const char *line);
t_cmd		*parse_command(const char *line);

void		cmd_init(t_cmd *cmd);
void		fill_cmd_array(const char *line, t_cmd *cmd);

int			builtin_echo(t_cmd cmd);



#endif