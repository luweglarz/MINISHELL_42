/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/06/14 21:02:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_builtin(const char *builtin)
{
	if (ft_strncmp(builtin, "echo", 4) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "cd", 4) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "pwd", 3) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "export", 6) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "unset", 5) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "env", 3) == 0)
		builtin_echo(1);
}

const char    *fill_builtin(const char *line, t_cmd *cmd)
{
    int     i;

    i = 0;
    while (ft_isascii(line[i]) == 1)
        i++;
    cmd->builtin = ft_substr(line, 0, i);
	i = 0;
	while ((size_t)i++ < ft_strlen(cmd->builtin))
		line++;
    return (line);
}

void	fill_cmd_array(const char *line, t_cmd *cmd)
{
	int	size;
	int	index;

    index = 0;
	while (*line)
	{
        printf("index %d\n", index);
        cmd_init(&cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_builtin(line, &cmd[index]);
        printf("builtin dans la func %s\n", cmd[index].builtin);
        if (cmd[index].builtin)
		    size = ft_strlen(cmd[index].builtin);
		while (*line == ' ')
			line++;
		cmd[index].cmd_index = index;
		index++;
	}	
}