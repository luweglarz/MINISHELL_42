/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/07/05 17:57:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_line(void)
{
	char	*line;

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

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int		main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	char	*tmp;
	char	**env_list;
	int		nb_cmd;
	cmd = NULL;
	(void)ac;
	(void)av;
	env_list = init_env(envp);
	signal(SIGINT, sig_handler);
	nb_cmd = 0;
	while (1)
	{
		line = get_line();
		tmp = replace_env_var(line, env_list, 0, 0);
		free(line);
		line = NULL;
		line = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		nb_cmd = parse_command(line);
		cmd = malloc(sizeof(t_cmd) * nb_cmd);
		fill_cmd_array(line, cmd);
		parse_cmd_array(cmd, env_list, nb_cmd);
		int i = 0;
		if (cmd)
		{
			if (cmd->arg)
			{
				while (cmd->arg[i])
				{
					free(cmd->arg[i]);
					i++;
				}
				free(cmd->arg);
			}
			if (cmd->builtin)
				free(cmd->builtin);
			free(cmd);
			cmd = NULL;
		}
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (1);
}
