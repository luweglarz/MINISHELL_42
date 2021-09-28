/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:40:13 by user42            #+#    #+#             */
/*   Updated: 2021/09/28 13:28:23 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_bracket_stuff(char *substr, struct stat *buf)
{
	free(substr);
	free(buf);
}

int	bracket_out_in(const char *line, int j, t_cmd *cmd, t_env_l *env)
{
	char		*file;
	struct stat	*buf;
	int			start;

	start = 0;
	j = j + 2;
	while (line[j] == ' ')
		j++;
	start = j;
	while ((ft_isascii(line[j]) == 1) && line[j] != '|')
		j++;
	file = ft_substr(line, start, j - start);
	buf = malloc(sizeof(struct stat) * 1);
	if (buf == NULL)
	{
		free_bracket_stuff(file, buf);
		error_errno(cmd, errno, true, env);
	}
	if (stat((const char *)file, buf) == -1)
		open(file, O_RDWR | O_CREAT, 0664);
	else
		cmd->fdin = open(file, O_RDWR);
	free_bracket_stuff(file, buf);
	cmd->fdout = 1;
	return (j);
}

int	bracket_out(const char *line, int j, t_cmd *cmd)
{
	char	*file;
	int		start;
	int		doublebracket;

	start = 0;
	doublebracket = 0;
	file = NULL;
	j = pass_brackets(line, j, &start, &doublebracket);
	file = ft_substr(line, start, j - start);
	if (doublebracket == 1)
		cmd->fdout = open(file, O_RDWR | O_APPEND | O_CREAT, 0664);
	else
		cmd->fdout = open(file, O_RDWR | O_CREAT, 0664);
	free(file);
	return (j);
}

static void	double_bracket_in(const char *file, t_cmd *cmd)
{
	int			fd;
	char		*newline;
	char		*join;

	join = ft_strjoin(TMPDIR, ".heredoc");
	fd = open(join, O_RDWR | O_CREAT, 0664);
	newline = NULL;
	while (1)
	{
		if (newline)
		{
			free(newline);
			newline = NULL;
		}
		newline = readline(">");
		if (newline)
			add_history(newline);
		if (ft_strncmp(newline, file, ft_strlen(file)) == 0)
			break ;
		write(fd, newline, ft_strlen(newline));
		write(fd, "\n", 1);
	}
	free(newline);
	cmd->fdin = open(join, O_RDWR);
	free(join);
}

int	bracket_in(const char *line, int j, t_cmd *cmd, t_env_l *env)
{
	char		*file;
	int			start;
	int			doublebracket;
	struct stat	*buf;

	start = 0;
	doublebracket = 0;
	j = pass_brackets(line, j, &start, &doublebracket);
	file = ft_substr(line, start, j - start);
	buf = malloc(sizeof(struct stat) * 1);
	if (buf == NULL)
		error_errno(cmd, errno, true, env);
	if (doublebracket == 1)
		double_bracket_in(file, cmd);
	else if (stat((const char *)file, buf) == -1 && doublebracket == 0)
	{
		cmd->fdin = -1;
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else
		cmd->fdin = open(file, O_RDWR);
	free(buf);
	free(file);
	return (j);
}
