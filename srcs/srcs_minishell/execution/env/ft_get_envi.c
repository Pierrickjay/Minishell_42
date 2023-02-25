/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_envi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:10:37 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 15:10:51 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	*ft_getenvi(char *name, t_envi *envi)
{
	while (envi)
	{
		if (ft_strcmp(envi->key, name) == 0)
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}
