/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:41:02 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 17:54:31 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// print the list
void	ft_envi_print(t_exec *exec, t_envi *envi)
{
	if (!envi)
		return ;
	while (envi)
	{
		if
		(
			ft_putstr_fd("declare -x ", STDOUT) == FAILURE || \
			ft_putstr_fd(envi->key, STDOUT) == FAILURE
		)
			return (ft_msg(exec, EXPORT_ERROR, errno, &exit));
		if (envi->type == NORMAL)
		{
			if
			(
				ft_putstr_fd("=\"", STDOUT) == FAILURE || \
				ft_putstr_fd(envi->value, STDOUT) == FAILURE || \
				ft_putendl_fd("\"", STDOUT) == FAILURE
			)
				return (ft_msg(exec, EXPORT_ERROR, errno, &exit));
		}
		envi = envi->next;
	}
}
