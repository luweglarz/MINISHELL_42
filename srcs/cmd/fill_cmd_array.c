/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/07/13 15:05:34 by user42           ###   ########.fr       */
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

int	create_redirection_files(const char *line, int *j, t_cmd *cmd)
{
	if (line[*j] == '>')
		*j = bracket_out(line, j, cmd);
	else if (line[*j] == '<')
		*j = bracket_in(line, j, cmd);
	return (*j);
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
		j = create_redirection_files(line, &j, cmd);
		newarg[k] = line[j];
		k++;
		j++;
	}
	newarg[k] = '\0';
	printf("le newarg %s\n", newarg);
	return (newarg);
}

static const char	*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*args;

	i = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		if (line[i] == '|' || line[i] == ';')
			break ;
		i++;
	}
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
		if (*line++ == '|')
			cmd[index].pipe = true;
		else if (*line++ == ';')
		{
			index++;
			continue ;
		}
		index++;
	}
	cmd_init(&cmd[index]);
}
