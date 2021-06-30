/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:06:34 by ugtheven          #+#    #+#             */
/*   Updated: 2021/06/30 20:52:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_command(int *cmd_started, int *nb_cmd)
{
	if (*cmd_started == 1)
	{
		nb_cmd++;
		cmd_started = 0;
	}
}

int	count_command(const char *line, int i)
{
	int	nb_cmd;
	int	inquote;
	int	cmd_started;

	nb_cmd = 0;
	inquote = 0;
	cmd_started = 0;
	if (line[i] != '\0')
		cmd_started = 1;
	while (line[i])
	{
		inquote = check_inquote(line, i, inquote);
		if ((line[i] == ';' || line[i] == '|') && inquote == 0)
			close_command(&cmd_started, &nb_cmd);
		else if ((size_t)i + 1 == ft_strlen(line) && cmd_started == 1)
		{
			nb_cmd++;
			break ;
		}
		else if (cmd_started == 0 && (size_t)i < ft_strlen(line)
			&& not_only_space(&line[i]) == 1)
			cmd_started = 1;
		i++;
	}
	return (nb_cmd);
}

int	parse_command(const char *line)
{
	int	nb_cmd;
	int	i;

	i = 0;
	nb_cmd = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == ';' || line[i] == '|' || check_sep(line) == -1)
		nb_cmd = -1;
	if (nb_cmd == 0)
		nb_cmd = count_command(line, i);
	if (nb_cmd < 0)
	{		
		printf("Erreur de separateur\n");
		exit(0);
	}
	printf("Il y a %d commandes\n", nb_cmd);
	return (nb_cmd);
}
