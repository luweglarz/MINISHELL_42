/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/06/25 22:02:59 by user42           ###   ########.fr       */
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

static const char	*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;
	char	*args;

	i = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		if (line[i] == '|' || line[i] == ';')
			break ;
		i++;
	}
	cmd->arg = malloc(sizeof(char *) * 2);
	cmd->arg[0] = ft_strschr(cmd->builtin, '/');
	args = ft_substr(line, 0, i);
	if (!args || ft_strlen(args) == 0)
		cmd->arg[1] = NULL;
	else
		cmd->arg[1] = ft_strdup(args);
	i = 0;
	while ((size_t)i++ < ft_strlen(args))
		line++;
	free(args);
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
		if (*line++ == ';')
		{
			index++;
			continue ;
		}
		while (*line == ' ')
			line++;
		line = fill_arg(line, &cmd[index]);
		if (*line++ == '|')
			cmd[index].pipe = true;
		index++;
	}	
}
