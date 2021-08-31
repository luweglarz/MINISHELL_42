/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/31 15:46:37 by ugtheven         ###   ########.fr       */
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

void	free_after_line(char *line)
{
	struct stat	*buf;
	char		*join;

	join = ft_strjoin(TMPDIR, ".heredoc");
	buf = malloc(sizeof(struct stat) * 1);
	if (stat(join, buf) == 0)
		unlink(join);
	free(buf);
	free(join);
	if (line)
	{
		free(line);
		line = NULL;
	}
}

char	*remove_quotes(char *expanded)
{
	int i;
	int inquote;
	int stop;
	char *newline;
	char *tmp;
	char *content;

	i = 0;
	inquote = 0;
	stop = -1;
	while (expanded[i])
	{
		inquote = check_inquote(expanded[i], inquote);
		if (inquote == 1 || inquote == 2)
			inquote = check_solo_quote(&expanded[i], inquote);
		if (inquote == 1)
		{
			//Je recupere ce qui se trouve avant les quotes
			if (stop == -1 && i > 0)
				tmp = ft_substr(expanded, 0, i - 1);
			else if (stop != i)
				tmp = ft_substr(expanded, stop, i - 1);
			else
				tmp = ft_strdup("");
			//je pose mon stop
			stop = i;
			//je recupere le contenu des quotes
			while (expanded[i] && inquote == 1)
			{
				inquote = check_inquote(expanded[i], inquote);
				i++;
			}
			content = ft_substr(expanded, stop, i - stop);
			
		}
		else if (inquote == 2)
		{
			newline = ft_substr()
		}
		i++;
	}
}

void	treat_cmd(int nb_cmd, t_pars *exp, t_env_l *env, char *line)
{
	char *tmp;
	t_cmd *cmd;
	char	*expanded;

	tmp = expand_env_value(exp, line, env);
	expanded = remove_quotes(tmp);
	free(tmp);
	printf("EXPANDED =%s\n", expanded);
	nb_cmd = parse_command(expanded);
	cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
	fill_cmd_array(expanded, cmd);
	int i = 0;
	while (cmd->arg[i])
	{
		printf("ARG[%d]=%s\n", i, cmd->arg[i]);
		i++;
	}
	//del_quotes(cmd, nb_cmd);
	parse_cmd_array(cmd, env, nb_cmd);
	free(expanded);
	free_cmd(cmd);
	free_after_line(line);
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

void	exit_free_env(t_env_l *env, int nb)
{
	int i;
	int j;

	i = 0;
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	i = 0;
	while (env->token[i])
	{
		j = 0;
		while (env->token[i][j])
		{
			free(env->token[i][j]);
			j++;
		}
		free(env->token[i]);
		i++;
	}
	free(env->token);
	exit(nb);
}

int	main(int ac, char **av, char **envp)
{
	t_pars exp;
	char	*line;
	t_env_l	env;
	int		nb_cmd;

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
			exit_free_env(&env, 0);
		nb_cmd = parse_command(line);
		if (nb_cmd >= 0)
			treat_cmd(nb_cmd, &exp, &env, line);
		else
			free_after_line(line);
	}
	return (1);
}
