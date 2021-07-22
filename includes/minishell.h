/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:13:53 by lweglarz          #+#    #+#             */
/*   Updated: 2021/07/22 15:53:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>

#if defined(__linux__)
    #define PLATFORM_NAME "linux" 
    # include <linux/limits.h>
#elif defined(__MACH__)
    # define PATH_MAX 1024
#endif

# include "cmd.h"
# include "builtin.h"
# include "parsing.h"
# include "lib.h"
# include "env.h"

char	*get_line(const char *prompt);
void	free_cmd(t_cmd *cmd);
void	error_errno(t_cmd *cmd, int error_code, bool exit_bool);

#endif