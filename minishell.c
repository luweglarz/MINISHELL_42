/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/08/23 18:26:59 by user42           ###   ########.fr       */
=======
/*   Updated: 2021/08/23 19:43:39 by user42           ###   ########.fr       */
>>>>>>> 4504fc53b30b94c58d35189fef8fb32f70eeafe1
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
	char		*join;

	join = ft_strjoin(TMPDIR, ".heredoc");
	buf = malloc(sizeof(struct stat) * 1);
	if (stat(join, buf) == 0)
		unlink(join);
	free(buf);
	free(join);
	free_cmd(cmd);
	if (line)
	{
		free(line);
		line = NULL;
	}
}

void	treat_cmd(t_cmd *cmd, int nb_cmd, t_env_l *env, char *line)
{
	cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
	fill_cmd_array(line, cmd);
	format_args(cmd, env->list, nb_cmd);
	del_quotes(cmd, nb_cmd);
	parse_cmd_array(cmd, env, nb_cmd);
	free_after_line(cmd, line);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env_l	env;
	int		nb_cmd;

	cmd = NULL;
	env.list = init_env(envp, ac, av);
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
			treat_cmd(cmd, nb_cmd, &env, line);
		else
			free_after_line(cmd, line);
	}
	return (1);
}
