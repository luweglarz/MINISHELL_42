/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/06/21 13:59:53 by lweglarz         ###   ########.fr       */
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
	int		j;

	i = 0;
	line++;
	while (line[i] == 'n')
		i++;
	if (i > 0 && (line[i] == ' ' || line[i] == '\0' || line[i] == ';'))
	{
		cmd->option = ft_strdup("-n");
		j = 0;
		while (j++ < i)
			line++;
	}
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
	args = ft_substr(line, 0, i);
	if (ft_strncmp(cmd->builtin, "echo", 4) == 0)
	{
		cmd->arg = malloc(sizeof(char*) * 1);
		cmd->arg[0] = args;
	}
	else
		cmd->arg = ft_split(args, ' ');
	i = 0;
	while ((size_t)i++ < ft_strlen(args))
		line++;
	return (line);
}

void	fill_cmd_array(const char *line, t_cmd *cmd)
{
	int		index;

	index = 0;
	while (*line)
	{
		printf("index %d\n", index);
		cmd_init(&cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_builtin(line, &cmd[index]);
		if (*line++ == ';')
		{	
			index++;
			continue ;
		}
		printf("Builtin: %s\n", cmd[index].builtin);
		while (*line == ' ')
			line++;
		if (ft_strncmp(cmd[index].builtin, "echo", 4) == 0 && *line == '-')
			line = fill_option(line, &cmd[index]);
		printf("Option: %s\n", cmd[index].option);
		while (*line == ' ')
			line++;
		line = fill_arg(line, &cmd[index]);
		for (int i = 0; cmd[index].arg[i]; i++)
			printf("Arg: %s\n", cmd[index].arg[i]);
		if (*line++ == '|')
			cmd[index].pipe = true;
		printf("Pipe: %d\n", cmd[index].pipe);
		index++;
	}	
}
