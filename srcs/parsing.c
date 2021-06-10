/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:06:34 by ugtheven          #+#    #+#             */
/*   Updated: 2021/06/10 15:37:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_sep(const char *line)
{
	int i;
	int inquote;

	i = 0;
	inquote = 0;
	while (line[i])
	{
		//check si on se trouve dans une simple ou double quote
		if (line[i] == '\'' && inquote == 0)
			inquote == 1;
		else if (line[i] == '"' && inquote == 0)
			inquote == 2;
		else if (line[i] == '\'' && inquote == 1)
			inquote == 0;
		else if (line[i] == '"' && inquote == 2)
			inquote == 0;
		//si on est sur un sep, on verifie qu'il n'y en ai pas un deuxieme sep derriere sans instruction entre
		if ((line[i] == ';' || line[i] == '|') && inquote == 0)
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == ';' || line[i] == '|')
				return (-1);
		}
		i++;
	}
	return (1);
}

int	not_only_space(const char *line)
{
	int i;
	int others;

	i = 0;
	others = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			others++;
		i++;
	}
	if (others == 0)
		return (-1);
	else
		return (1);
}

int	count_command(const char *line)
{
	int i;
	int nb_cmd;
	int	inquote;
	int cmd_started;

	i = 0;
	nb_cmd = 0;
	inquote = 0;
	cmd_started = 0;
	//je passe les espaces
	while (line[i] && line[i] == ' ')
		i++;
	//si le premier char apres les espaces est une separation erreur de separation
	if (line[i] == ';' || line[i] == '|' || check_sep(line) == -1)
		return (-1);
	else if (line[i] != '\0')
		cmd_started = 1;
	while (line[i])
	{
		//check si on se trouve dans une simple ou double quote
		if (line[i] == '\'' && inquote == 0)
			inquote == 1;
		else if (line[i] == '"' && inquote == 0)
			inquote == 2;
		else if (line[i] == '\'' && inquote == 1)
			inquote == 0;
		else if (line[i] == '"' && inquote == 2)
			inquote == 0;
		//si il y a un separateur et que inquote == 0, on compte une commande
		if ((line[i] == ';' || line[i] == '|') && inquote == 0)
		{
			// si cmd_started == 1 cest quune commande est commencer donc que l'on peut la terminer.
			if (cmd_started == 1)
			{
				nb_cmd++;
				cmd_started = 0;
			}
		}
		//si on arrive a la fin de la string et qu'une commande est commencer, on peut la terminer
		else if (i + 1 == ft_strlen(line) && cmd_started == 1)
		{
			nb_cmd++;
			break ;
		}
		else if (cmd_started == 0 && i < ft_strlen(line) && not_only_space(&line[i]) == 1)
			cmd_started = 1;
		//si il ny a pas de separateur on avance
		i++;
	}
	return (nb_cmd);
}

void	parse_command(const char *line)
{
	int	nb_cmd;
	t_cmd *cmd;
	int cmd_index;

	nb_cmd = count_command(line);
	cmd_index = 0;
	//si il y a une erreur de separateur, je quitte.
	if (nb_cmd == -1)
	{
		printf("Erreur de separateur\n");
		exit(0);
	}
	//je malloc ma structure si on a une commande
	else if (nb_cmd != 0)
		cmd = malloc(sizeof(t_cmd) * nb_cmd);
	//print test;
	printf("Il y a %d commandes\n", nb_cmd);
	//si il ma structure est malloc je la free
	if (nb_cmd > 0)
		free(cmd);
}

int	main(int ac, char **av)
{
	(void)ac;
	parse_command(av[1]);
	return (0);
}