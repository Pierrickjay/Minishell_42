/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:59:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:17:28 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// return the size of the list
size_t	ft_envi_size(t_envi *envi)
{
	size_t	size;

	size = 0;
	while (envi)
	{
		if (envi->type == NORMAL)
			size++;
		envi = envi->next;
	}
	return (size);
}
