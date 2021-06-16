/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 13:28:37 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		do_builtin(t_cmd cmd)
{
	if (ft_strncmp(cmd.builtin, "echo", 4) == 0 && cmd.error == false)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd.builtin, "cd", 4) == 0 && cmd.error == false)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd.builtin, "pwd", 3) == 0 && cmd.error == false)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd.builtin, "export", 6) == 0 && cmd.error == false)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd.builtin, "unset", 5) == 0 && cmd.error == false)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd.builtin, "env", 3) == 0 && cmd.error == false)
		builtin_echo(cmd);
	//else if (check_path())

//	else
//		return ;
}

bool		check_builtin(const char *builtin)
{
	if (ft_strncmp(builtin, "echo", 4) == 0)
		return (false);
	else if (ft_strncmp(builtin, "cd", 4) == 0)
		return (false);
	else if (ft_strncmp(builtin, "pwd", 3) == 0 )
		return (false);
	else if (ft_strncmp(builtin, "export", 6) == 0)
		return (false);
	else if (ft_strncmp(builtin, "unset", 5) == 0)
		return (false);
	else if (ft_strncmp(builtin, "env", 3) == 0)
		return (false);
	return (true);
}

const char	*fill_builtin(const char *line, t_cmd *cmd)
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

const char		*fill_option(const char *line, t_cmd *cmd)
{
	int 	i;

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

const char		*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		//if sep ou pipe do un truc
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
	int	index;

    index = 0;
	while (*line)
	{
        printf("index %d\n", index);
        cmd_init(&cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_builtin(line, &cmd[index]);
        printf("builtin: %s\n", cmd[index].builtin);
		while (*line == ' ')
			line++;
		if (ft_strncmp(cmd[index].builtin, "echo", 4) == 0)
			line = fill_option(line, &cmd[index]);
		printf("option: %s\n", cmd[index].option);
		while (*line == ' ')
			line++;
		line = fill_arg(line, &cmd[index]);
		printf("arg: %s\n", cmd[index].arg);
		//while (*line == ' ')
		//	line++;
		
		cmd[index].cmd_index = index;
		index++;
	}	
}