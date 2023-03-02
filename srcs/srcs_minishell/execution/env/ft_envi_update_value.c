/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_update_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:54:52 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/26 13:36:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_envi	*ft_envi_update_value(char *key, char *new_value, t_envi *envi)
{
	t_envi	*to_edit;
	t_envi	*top;

	to_edit = NULL;
	top = envi;
	while (envi)
	{
		if (ft_strcmp(envi->key, key) == 0)
		{
			to_edit = envi;
			break ;
		}
		envi = envi->next;
	}
	if (to_edit)
	{
		free(to_edit->value);
		to_edit->value = ft_strdup(new_value);
		if (!to_edit->value)
			return (NULL);
	}
	return (top);
}
