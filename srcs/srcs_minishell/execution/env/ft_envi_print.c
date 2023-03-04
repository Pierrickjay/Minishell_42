/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:41:02 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 15:57:20 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_envi_print(t_envi *envi)
{
	while (envi)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(envi->key, STDOUT);
		if (envi->type == NORMAL)
		{
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(envi->value, STDOUT);
		}
		ft_putstr_fd("\"\n", STDOUT);
		envi = envi->next;
	}
}
