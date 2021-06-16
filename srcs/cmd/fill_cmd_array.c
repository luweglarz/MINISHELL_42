/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 22:20:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*fill_builtin(const char *line, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (ft_isascii(line[i]) == 1)
		i++;
	cmd->builtin = ft_substr(line, 0, i);
	i = 0;
	while ((size_t)i++ < ft_strlen(cmd->builtin))
		line++;
	return (line);
}

static const char	*fill_option(const char *line, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (ft_strncmp(line, "-n ", 3) == 0)
	{
		cmd->option = ft_substr(line, 0, 2);
		i = 0;
		while ((size_t)i++ < ft_strlen(cmd->option))
			line++;
	}
	return (line);
}

static const char	*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		if (line[i] == '|' || line[i] == ';')
			break ;
		i++;
	}
	cmd->arg = ft_substr(line, 0, i);
	i = 0;
	while ((size_t)i++ < ft_strlen(cmd->arg))
		line++;
	return (line);
}

void	fill_cmd_array(const char *line, t_cmd *cmd)
{
	int		index;

	index = 0;
	while (*line)
	{
		cmd_init(&cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_builtin(line, &cmd[index]);
		while (*line == ' ')
			line++;
		if (ft_strncmp(cmd[index].builtin, "echo", 4) == 0)
			line = fill_option(line, &cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_arg(line, &cmd[index]);
		if (*line == ';' || *line == '|')
			cmd[index].sep = *line;
		index++;
	}	
}
