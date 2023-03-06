/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:45:50 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:17:05 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// return the last node of the list
t_envi	*ft_envi_last(t_envi *envi)
{
	while (envi && envi->next)
		envi = envi->next;
	return (envi);
}
