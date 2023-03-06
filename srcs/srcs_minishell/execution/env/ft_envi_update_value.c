/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_update_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:54:52 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 15:42:47 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	ft_envi_update_value_bis(t_envi **to_edit, int type, char *value)
{
	if ((*to_edit)->value)
		free((*to_edit)->value);
	(*to_edit)->type = type;
	(*to_edit)->value = ft_strdup(value);
	if (!(*to_edit)->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// update the value of a node in the list
t_envi	*ft_envi_update_value(char *key, char *value, int type, t_envi *envi)
{
	t_envi	*to_edit;
	t_envi	*top;

	if (!envi)
		return (NULL);
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
		if (ft_envi_update_value_bis(&to_edit, type, value))
			return (NULL);
	}
	return (top);
}
