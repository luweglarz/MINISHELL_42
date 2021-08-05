/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:28:44 by user42            #+#    #+#             */
/*   Updated: 2021/08/05 17:05:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_exit_code(t_pars *pars)
{
	char	*str;

	str = ft_itoa(g_err);
	pars->var_content = ft_strdup(str);
	free(str);
}
