/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/30 15:19:05 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
	char	*expanded;

	expanded = expand_env_value(line, env->list);
	nb_cmd = parse_command(expanded);
	printf("EXPANDED =%s\n", expanded);
	cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
	fill_cmd_array(expanded, cmd);
	/*int i = 0;
	while (cmd->arg[i])
	{
		printf("ARG[%d]=%s\n", i, cmd->arg[i]);
		i++;
	}*/
	del_quotes(cmd, nb_cmd);
	parse_cmd_array(cmd, env, nb_cmd);
	free(expanded);
	free_after_line(cmd, line);
}

void	init_token(t_env_l *env)
{
	char **var_contents;
	int i;
	int j;

	env->token = malloc(sizeof(char **) * (nb_env(env->list) + 1));
	var_contents = get_env_content(env->list);
	i = 0;
	while (var_contents[i])
	{
		env->token[i] = ft_split(var_contents[i], ' ');
		i++;
	}
	env->token[i] = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env_l	env;
	int		nb_cmd;

	cmd = NULL;
	env.list = init_env(envp, ac, av);
	init_token(&env);
	signal(SIGQUIT, sig_handler);
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
