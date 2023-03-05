/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:47:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:17:18 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// create a new node
t_envi	*ft_envi_new(char *key, char *value, int type)
{
	t_envi	*new;

	if (!key || !value)
		return (NULL);
	new = malloc(sizeof(t_envi));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}
