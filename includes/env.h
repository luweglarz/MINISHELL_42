#ifndef ENV_H
# define ENV_H

# include "minishell.h"

char	**envdup_without(int nb_env, char **env_list, char *without);
char	**envdup(int nb_env, char **env_list);
int		nb_env(char **env_list);
void	free_env(int nb_env, char **env_list);

#endif