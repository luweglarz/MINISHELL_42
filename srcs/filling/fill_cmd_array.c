/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/08/26 13:55:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*fill_builtin(const char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	do_beginning_bracket(&i, &start, line, cmd);
	while (ft_isascii(line[i]) == 1)
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			break ;
		i++;
	}
	cmd->builtin = ft_substr(line, start, i - start);
	while (j++ < i)
		line++;
	return (line);
}

static char	*formate_args(const char *line, t_cmd *cmd, int i)
{
	int		j;
	int		k;
	char	*newarg;

	j = 0;
	k = 0;
	newarg = malloc(sizeof(char) * (size_with_redirection(line, i) + 1));
	while (j < i)
	{	
		if (line[j] == '<' && line[j + 1] == '>')
			j = bracket_out_in(line, j, cmd);
		if (line[j] == '>')
			j = bracket_out(line, j, cmd);
		else if (line[j] == '<')
			j = bracket_in(line, j, cmd);
		if (line[j] != '<' && line[j] != '>')
		{
			newarg[k] = line[j];
			k++;
			j++;
		}
	}
	newarg[k] = '\0';
	return (newarg);
}

static const char	*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*args;

	i = 0;
	i = pass_ascii(line, i);
	args = formate_args(line, cmd, i);
	if (!args || ft_strlen(args) == 0)
	{
		cmd->arg = malloc(sizeof(char *) * 2);
		cmd->arg[0] = ft_strdup(cmd->builtin);
		cmd->arg[1] = NULL;
	}
	else
		cmd->arg = split_args(args, cmd->builtin);
	free(args);
	j = 0;
	while (j++ < i)
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
		line = fill_arg(line, &cmd[index]);
		if (*line == '|')
		{
			cmd[index].pipe = true;
			line++;
		}
		index++;
	}
	cmd_init(&cmd[index]);
}
