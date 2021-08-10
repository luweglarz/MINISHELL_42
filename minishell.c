/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/10 02:54:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

void	free_after_line(t_cmd *cmd, char *line)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat) * 1);
	free(buf);
	free_cmd(cmd);
	if (line)
	{
		free(line);
		line = NULL;
	}
}

void	treat_cmd(t_cmd *cmd, int nb_cmd, char **env_list, char *line)
{
	cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
	fill_cmd_array(line, cmd);
	format_args(cmd, env_list, nb_cmd);
	del_quotes(cmd, nb_cmd);
	parse_cmd_array(cmd, env_list, nb_cmd);
	free_after_line(cmd, line);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	char	**env_list;
	int		nb_cmd;

	cmd = NULL;
	env_list = init_env(envp, ac, av);
	signal(SIGINT, sig_handler);
	nb_cmd = 0;
	line = NULL;
	while (1)
	{
		line = readline("Minishell>");
		if (line)
			add_history(line);
		if (line == NULL)
			exit(0);
		nb_cmd = parse_command(line);
		if (nb_cmd >= 0)
			treat_cmd(cmd, nb_cmd, env_list, line);
		else
			free_after_line(cmd, line);
	}
	return (1);
}
