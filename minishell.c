/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/07/18 04:31:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_line(const char *prompt)
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(prompt);
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
	else if (signum == EOF)
		exit(1);
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

//MAIN
int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	char	**env_list;
	int		nb_cmd;

	cmd = NULL;
	(void)ac;
	(void)av;
	env_list = init_env(envp);
	signal(SIGINT, sig_handler);
	nb_cmd = 0;
	line = NULL;
	while (1)
	{
		line = readline("Minishell>");
		if (line)
			add_history(line);
		if (line == NULL)
			exit(1);
		nb_cmd = parse_command(line);
		if (nb_cmd >= 0)
		{
			cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
			fill_cmd_array(line, cmd);
			format_args(cmd, env_list, nb_cmd);
			del_quotes(cmd, nb_cmd);
			parse_cmd_array(cmd, env_list, nb_cmd);
			free_after_line(cmd, line);
		}
		else if (line)
			free(line);
	}
	return (1);
}
