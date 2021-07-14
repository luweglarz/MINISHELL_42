/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:40:13 by user42            #+#    #+#             */
/*   Updated: 2021/07/12 20:18:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bracket_out(const char *line, int *j, t_cmd *cmd)
{
	char	*file;
	int		start;
	int		doublebracket;

	start = 0;
	doublebracket = 0;
	file = NULL;
	*j = pass_redirections(line, *j, &start, &doublebracket);
	file = ft_substr(line, start, *j - start);
	if (doublebracket == 1)
		cmd->fdout = open(file, O_RDWR | O_APPEND | O_CREAT, 0664);
	else
		cmd->fdout = open(file, O_RDWR | O_CREAT, 0664);
	return (*j);
}

static void	double_bracket_in(const char *file, t_cmd *cmd)
{
	int			fd;
	char		*newline;

	fd = open(".heredoc", O_RDWR | O_CREAT, 0664);
	while (1)
	{
		newline = get_line(">");
		if (ft_strncmp(newline, file, ft_strlen(file)) == 0)
			break ;
		write(fd, newline, ft_strlen(newline));
		write(fd, "\n", 1);
	}
	free(newline);
	cmd->fdin = open(".heredoc", O_RDWR);
}

int	bracket_in(const char *line, int *j, t_cmd *cmd)
{
	char		*file;
	int			start;
	int			doublebracket;
	struct stat	*buf;

	start = 0;
	doublebracket = 0;
	file = NULL;
	*j = pass_redirections(line, *j, &start, &doublebracket);
	file = ft_substr(line, start, *j - start);
	buf = malloc(sizeof(buf) * 1);
	if (buf == NULL)
		error_errno(cmd, errno, true);
	if (doublebracket == 1)
		double_bracket_in(file, cmd);
	else if (stat(file, buf) == -1 && doublebracket == 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else
		cmd->fdin = open(file, O_RDWR);
	free(buf);
	free(file);
	return (*j);
}
