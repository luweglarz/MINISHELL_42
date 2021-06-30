#ifndef ENV_H
# define ENV_H

# include "minishell.h"

int		var_exist(t_cmd cmd, char **env_list);
int		nb_env(char **env_list);
void	free_env(int nb_env, char **env_list);
char	**get_env_names(char **env_list);
void		free_env_list(int nb_env, char **env_list);

#endif