/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:41:02 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:17:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// print the list
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
			ft_putchar_fd('\"', STDOUT);
		}
		ft_putchar_fd('\n', STDOUT);
		envi = envi->next;
	}
}
