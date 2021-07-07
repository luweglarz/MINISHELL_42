/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/07/07 16:51:31 by user42           ###   ########.fr       */
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
		if (line[i] == '|' || line[i] == ';' || line[i] == '>'
		 || line[i] == '<' || ft_strncmp(line, ">>", 2) == 0 
		 || ft_strncmp(line, "<<", 2) == 0)
			break ;
		i++;
	}
	args = ft_substr(line, 0, i);
	if (!args || ft_strlen(args) == 0)
	{
		cmd->arg = malloc(sizeof(char *) * 2);
		cmd->arg[0] = ft_strdup(cmd->builtin);
		cmd->arg[1] = NULL;
	}
	else
		cmd->arg = split_args(args, cmd->builtin);
	i = 0;
	while ((size_t)i++ < ft_strlen(args))
		line++;
	free(args);
	return (line);
}

static const char	*check_flows(const char *line, t_cmd *cmd)
{
	if (*line == '>' || *line == '<')
	{
		if (ft_strncmp(line, ">>", 2) == 0)
		{
			cmd->flows = ft_strdup(">>");
			line++;
		}
		else if (ft_strncmp(line, "<<", 2) == 0)
		{
			cmd->flows = ft_strdup("<<");
			line++;
		}
		else if (*line == '>')
			cmd->flows = ft_strdup(">");
		else if (*line == '<')
			cmd->flows = ft_strdup("<");
		line++;	
	}
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
	//	line = check_flows(line, &cmd[index]);
		line = fill_arg(line, &cmd[index]);
		if (*line == '|')
		{
			cmd[index].pipe = true;
			line++;
		}
		else if (*line == ';')
		{
			line++;
			index++;
			continue;
		}
		line = check_flows(line, &cmd[index]);
		printf("le flows %s\n", cmd[index].flows);
		index++;
	}
	cmd_init(&cmd[index]);
}