/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:06:34 by ugtheven          #+#    #+#             */
/*   Updated: 2021/07/14 02:43:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_command(int *cmd_started, int *nb_cmd)
{
	if (*cmd_started == 1)
	{
		*nb_cmd = *nb_cmd + 1;
		*cmd_started = 0;
	}
}

int	count_command(const char *line, int i, int len, int	inquote)
{
	int	nb_cmd;
	int	cmd_started;

	nb_cmd = 0;
	cmd_started = 0;
	if (line[i] != '\0')
		cmd_started = 1;
	while (line[i])
	{
		inquote = check_inquote(line[i], inquote);
		if ((line[i] == ';' || line[i] == '|') && inquote == 0)
			close_command(&cmd_started, &nb_cmd);
		else if (i + 1 == len && cmd_started == 1)
		{
			nb_cmd++;
			break ;
		}
		else if (cmd_started == 0
			&& i < len && not_only_space(&line[i]) == 1)
			cmd_started = 1;
		i++;
	}
	return (nb_cmd);
}

int	check_line(const char *line)
{
	if (check_sep(line) < 0)
		return (-1);
	if (check_redirection(line) < 0)
		return (-2);
	if (check_unclosed(line) < 0)
		return (-3);
	if (check_unused(line) < 0)
		return (-4);
	return (0);
}

int	parse_command(const char *line)
{
	int	nb_cmd;
	int	i;

	i = 0;
	nb_cmd = 0;
	if (check_line(line) < 0)
	{
		if (check_line(line) == -1)
			printf("Parsing : Erreur de syntax (separator ';' '|').\n");
		else if (check_line(line) == -2)
			printf("Parsing : Erreur de syntax (redirection '>' '<').\n");
		else if (check_line(line) == -3)
			printf("Parsing : Erreur de syntax (unclosed quotes \"').\n");
		else if (check_line(line) == -4)
			printf("Parsing : Erreur de syntax (something missing).\n");
		return (-1);
	}
	while (line[i] && line[i] == ' ')
		i++;
	nb_cmd = count_command(line, i, ft_strlen(line), 0);
	return (nb_cmd);
}
