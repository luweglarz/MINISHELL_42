/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:06:34 by ugtheven          #+#    #+#             */
/*   Updated: 2021/06/21 12:32:01 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_inquote(const char *line, int i, int inquote)
{
	if (line[i] == '\'' && inquote == 0)
		return (1);
	else if (line[i] == '"' && inquote == 0)
		return (2);
	else if (line[i] == '\'' && inquote == 1)
		return (0);
	else if (line[i] == '"' && inquote == 2)
		return (0);
	else 
		return (inquote);
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
			inquote = 1;
		else if (line[i] == '"' && inquote == 0)
			inquote = 2;
		else if (line[i] == '\'' && inquote == 1)
			inquote = 0;
		else if (line[i] == '"' && inquote == 2)
			inquote = 0;
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
		inquote = check_inquote(line, i, inquote);
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
		else if ((size_t)i + 1 == ft_strlen(line) && cmd_started == 1)
		{
			nb_cmd++;
			break ;
		}
		else if (cmd_started == 0 && (size_t)i < ft_strlen(line) && not_only_space(&line[i]) == 1)
			cmd_started = 1;
		//si il ny a pas de separateur on avance
		i++;
	}
	return (nb_cmd);
}

int	parse_command(const char *line)
{
	int	nb_cmd;
	int cmd_index;

	nb_cmd = count_command(line);
	cmd_index = 0;
	//si il y a une erreur de separateur, je quitte.
	if (nb_cmd < 0)
	{		
		printf("Erreur de separateur\n");
		exit(0);
	}
	printf("Il y a %d commandes\n", nb_cmd);
	return (nb_cmd);
}
