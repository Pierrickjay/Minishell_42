/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:45:50 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 15:38:55 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// return the last node of the list
t_envi	*ft_envi_last(t_envi *envi)
{
	if (!envi)
		return (NULL);
	while (envi && envi->next)
		envi = envi->next;
	return (envi);
}
