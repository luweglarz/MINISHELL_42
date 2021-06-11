/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/06/10 22:43:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char    *get_line()
{
    char *line;

    line = NULL;
    if (line)
    {
        free(line);
        line = NULL;
    }
    line = readline("Minishell>");
    if (line)
        add_history(line);
    return (line);
}

void	cmd_init(t_cmd *cmd)
{
	cmd->arg = NULL;
	cmd->builtin = NULL;
	cmd->option = NULL;
	cmd->error = NULL;
	cmd->cmd_index = 0;
}

char	*fill_builtin(const char *line)
{
	if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_strdup("echo"));
	else if (ft_strncmp(line, "cd", 4) == 0)
		return (ft_strdup("cd"));
	else if (ft_strncmp(line, "pwd", 3) == 0)
		return (ft_strdup("pwd"));
	else if (ft_strncmp(line, "export", 6) == 0)
		return (ft_strdup("export"));
	else if (ft_strncmp(line, "unset", 5) == 0)
		return (ft_strdup("unset"));
	else if (ft_strncmp(line, "env", 3) == 0)
		return (ft_strdup("env"));
}

void	fill_cmd_array(const char *line, t_cmd *cmd)
{
	int	size;
	int	index;
	while (*line)
	{
		if (*line == " ")
			*line++;
		cmd[index].builtin = fill_builtin(line);
		size = ft_strlen(cmd[index].builtin);
		while (size--)
			*line++;
		if (*line == " ")
			*line++;
		if (ft_strncmp(cmd[index].builtin, "echo", 4) == 0)

		cmd[index].cmd_index = index;
		index++;
		//*line++;
	}
	
}

int main(void)
{
	t_cmd 	*cmd;
    char 	*line;

	cmd = NULL;
    while (1)
	{
		cmd_init(cmd);
        line = get_line();
		cmd = parse_command(line);
		fill_cmd_array(line, cmd);
		if (strncmp(line, "pwd", 3) == 0)
		{
			cmd[0].builtin = ft_strdup("pwd");
			builtin_pwd(cmd);
		}
		if (cmd)
			free(cmd);
	}
}
