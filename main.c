/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/06/17 18:44:21 by user42           ###   ########.fr       */
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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

char	*get_var_name(const char *line)
{
	char *var_name;
	int len;
	int i;
	int j;

	len = 1;
	while (line[len] && line[len] != ' ' && line[len] != '\'' && line[len] != '"')
		len++;
	var_name = malloc(sizeof(char) * len);
	i = 1;
	j = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '"')
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
	char *str;
	char *temp;
	int start;
	int end;

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
	int i;
	int len;

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

char	*expand_var_content(const char *line, char **env_list, int space)
{
	char *var_name;
	char *var_content;
	char *tmp;
	int i;
	int j;

	var_name = get_var_name(line);
	var_content = NULL;
	tmp = NULL;
	printf("DEBUG : var_name = %s | len = %zu\n", var_name, ft_strlen(var_name));
	if (getenv(var_name) != NULL)
		tmp = ft_getenv(var_name, env_list);
	printf("DEBUG : var_content = %s | tmp = %s\n", var_content, tmp);
	if (var_name)
		free(var_name);
	i = 0;
	j = 0;
	//si je dois enlever les espaces, je les enleve et je mets la string entre guillement
	if (tmp && space == 0)
	{
		var_content = strdup_without_space(tmp);
		if (tmp)
			free(tmp);
		return (var_content);
	}
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
		if (tmp)
			free(tmp);
		return (var_content);
	}
	else
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
}

char	*del_dollar(const char *line, char quote)
{
	char *expanded;
	int stop;
	int inquote;
	int i;

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

char	*replace_env_var(const char *line, char **env_list)
{
	char *expanded;
	int i;
	int inquote;

	expanded = NULL;
	i = 0;
	inquote = 0;
	while (line[i])
	{
		inquote = check_inquote(line, i, inquote);
		if (line[i] == '$' && (inquote == 0 || inquote == 2))
		{
			//si le $ est dans des doubles guillemets on expand le contenu de la variable dans sa totalite si elle existe
			if (inquote == 2)
			{
				expanded = expand_var_content(&line[i], env_list, 1);
				return (expanded);
			}
			//si il n'y a pas de guillemet avant le $ je passe au caractere suivant
			else if (i < (int)ft_strlen(line))
			{
				inquote = check_inquote(line, i + 1, inquote);
				//si le $ n'est dans aucun guillemet on expand le contenu de la variable sans les espaces aux extremites si elle existe
				//et on met un espace a la suite.
				if (inquote == 0)
					expanded = expand_var_content(&line[i], env_list, 0);
				//si le $ est suivi d'une string entre guillement simple ou double, on enleve le dollar
				else if (inquote == 1)
					expanded = del_dollar(&line[i], '\'');
				else
					expanded = del_dollar(&line[i], '"');
				return (expanded);
			}
			i++;
		}
		i++;
	}
	return (expanded);
}

char	**init_env(char **envp)
{
	char **env_list;
	int i;

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

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	char	*tmp;
	char	**env_list;

	cmd = NULL;
	(void)ac;
	(void)av;
	env_list = init_env(envp);
	signal(SIGINT, sig_handler);
	while (1)
	{
		line = get_line();
		//test
		tmp = replace_env_var(line, env_list);
		printf("TMP(expanded) = %s\n", tmp);
		cmd = parse_command(line);
		fill_cmd_array(line, cmd);
		parse_cmd_array(cmd);
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
