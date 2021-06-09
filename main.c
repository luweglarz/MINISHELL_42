/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/06/09 17:01:11 by user42           ###   ########.fr       */
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
}

int main(void)
{
	t_cmd 	cmd;
    char 	*line;

    while (1)
	{
		cmd_init(&cmd);
        line = get_line();
		//parse_line(line);
		if (strncmp(line, "pwd", 3) == 0)
		{
			cmd.builtin = ft_strdup("pwd");
			builtin_pwd(cmd);
		}
	}
}
