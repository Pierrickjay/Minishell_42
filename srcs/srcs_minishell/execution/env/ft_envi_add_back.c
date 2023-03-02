/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:47:07 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 11:32:55 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_envi_add_back(t_envi **envi, t_envi *new)
{
	t_envi	*last;

	if (!envi || !new)
		return ;
	if (!*envi)
	{
		*envi = new;
		return ;
	}
	last = ft_envi_last(*envi);
	last->next = new;
}
