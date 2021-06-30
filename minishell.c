/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/06/30 22:42:58 by user42           ###   ########.fr       */
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

/*void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}*/

/*#########################################################*/
/*#########################  UGO  #########################*/
/*#########################################################*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*join;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (join == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*get_var_name(const char *line, int *index)
{
	char	*var_name;
	int		i;
	int		j;

	j = 0;
	i = *index;
	while (line[*index] && line[*index] != ' ' && line[*index] != '\'' && line[*index] != '"'
		&& line[*index] != ';' && line[*index] != '|' && line[*index] != '$')
	{
		*index = *index + 1;
		j++;
	}
	var_name = malloc(sizeof(char) * j + 1);
	j = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '"'
		&& line[i] != ';' && line[i] != '|' && line[i] != '$')
	{
		var_name[j] = line[i];
		i++;
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}

char	*strdup_without_space(char *tmp)
{
	char	*str;
	char	*temp;
	int		start;
	int		end;

	start = 0;
	end = (int)ft_strlen(tmp);
	while (tmp[start] && tmp[start] == ' ')
		start++;
	while (end > 0 && tmp[end] == ' ')
		end--;
	str = ft_substr(tmp, start, end);
	temp = ft_strjoin("\"", str);
	free(str);
	str = ft_strjoin(temp, "\"");
	free(temp);
	return (str);
}

char	*ft_getenv(char *var_name, char **env_list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env_list[i] != NULL)
	{
		if (env_list[i] && ft_strncmp(env_list[i], var_name, len) == 0 && env_list[i][len] == '=')
			return (ft_substr(env_list[i], len + 1, ft_strlen(env_list[i])));
		i++;
	}
	return (NULL);
}

char	*expand_var_content(const char *line, int *index, char **env_list, int space)
{
	char	*res;
	char	*var_name;
	char	*var_content;
	char	*tmp;
	int		i;
	int		j;

	var_name = get_var_name(line, index);
	var_content = NULL;
	tmp = NULL;
	res = NULL;
	i = 0;
	j = 0;
	if (getenv(var_name) != NULL)
		tmp = ft_getenv(var_name, env_list);
	if (var_name)
		free(var_name);
	//si je dois enlever les espaces, je les enleve et je mets la string entre guillement
	if (tmp && space == 0)
		var_content = strdup_without_space(tmp);
	//si je dois conserver les espaces et je mets la string entre guillement
	else if (tmp && space == 1)
	{
		var_content = malloc(sizeof(char) * ft_strlen(tmp) + 3);
		var_content[0] = '"';
		while (tmp[i])
		{
			var_content[i + 1] = tmp[i];
			i++;
		}
		var_content[ft_strlen(tmp) + 1] = '"';
		var_content[ft_strlen(tmp) + 2] = '\0';
		
	}
	if (tmp)
		free(tmp);
	return(var_content);
}

char	*del_dollar(const char *line, char quote)
{
	char	*expanded;
	int		stop;
	int		inquote;
	int		i;

	stop = 1;
	inquote = 0;
	while (line[stop])
	{
		inquote = check_inquote(line, stop, inquote);
		if (inquote == 0)
			break;
		stop++;
	}
	expanded = malloc(sizeof(char) * stop + 1);
	i = 0;
	while (line[i + 1])
	{
		expanded[i] = line[i + 1];
		i++;
	}
	expanded[0] = quote;
	expanded[stop - 1] = quote;
	expanded[stop] = '\0';
	return (expanded);
}

char	*replace_env_var(const char *line, char **env_list, int i, int stop)
{
	char	*expanded;
	int		inquote;
	char	*res;
	char	*tmp;
	char	*tmp2;

	inquote = 0;
	expanded = NULL;
	res = NULL;
	tmp = NULL;
	tmp2 = NULL;
	while (line[i])
	{
		inquote = check_inquote(line, i, inquote);
		if (line[i] == '$' && (inquote == 0 || inquote == 2))
		{
			if (res == NULL && inquote == 2)
				res = ft_substr(line, 0, i - 1);
			else if (res == NULL)
				res = ft_substr(line, 0, i);
			else if (line[stop + i - stop])
				tmp2 = ft_substr(line, stop, i - stop);
			i++;
			if (inquote == 2)
				expanded = expand_var_content(line, &i, env_list, 1);
			else if (i < (int)ft_strlen(line) && line[i] != ';' && line[i + 1] && line[i + 1] != ' ')
			{
				inquote = check_inquote(line, i, inquote);
				if (inquote == 0)
					expanded = expand_var_content(line, &i, env_list, 0);
				else if (inquote == 1)
					expanded = del_dollar(&line[i], '\'');
				else
					expanded = del_dollar(&line[i], '"');
			}
			else
				expanded = ft_strdup("$");
			stop = i;
		}
		if (expanded || tmp2)
		{
			if (tmp2)
			{
				tmp = ft_strdup(res);
				free(res);
				res = NULL;
				res = ft_strjoin(tmp, tmp2);
				free(tmp);
				tmp = NULL;
				free(tmp2);
				tmp2 = NULL;
			}
			if (expanded)
			{
				tmp = ft_strdup(res);
				free(res);
				res = ft_strjoin(tmp, expanded);
				free(tmp);
				tmp = NULL;
				free(expanded);
				expanded = NULL;
			}
		}
		if (i < (int)ft_strlen(line) && line[i] != '$')
			i++;
	}
	if (res == NULL)
		res = ft_substr(line, 0, i);
	else if (stop != i)
	{
		tmp = ft_strdup(res);
		tmp2 = ft_substr(line, stop, i - stop);
		free(res);
		res = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
	}
	return (res);
}

char	**init_env(char **envp)
{
	char	**env_list;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env_list = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		env_list[i] = ft_strdup(envp[i]);
		i++;
	}
	env_list[i] = NULL;
	return (env_list);
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
	//signal(SIGINT, sig_handler);
	nb_cmd = 0;
	while (1)
	{
		line = get_line();
		tmp = replace_env_var(line, env_list, 0, 0);
		free(line);
		line = ft_strdup(tmp);
		free(tmp);
		nb_cmd = parse_command(line);
		cmd = malloc(sizeof(t_cmd) * nb_cmd);
		fill_cmd_array(line, cmd);
		parse_cmd_array(cmd, env_list, nb_cmd);
		if (cmd)
		{
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
