/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:35:59 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:10:48 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// duplicate the enviroment list
t_envi	*ft_dup_envi(t_envi *envi)
{
	t_envi	*dup;
	t_envi	*tmp;
	char	*key;
	char	*value;

	dup = NULL;
	while (envi)
	{
		key = ft_strdup(envi->key);
		value = ft_strdup(envi->value);
		if (!key || !value)
			return (ft_free_envi(dup), ft_msg(NULL, NULL, MA, NULL), NULL);
		tmp = ft_envi_new(key, value, envi->type);
		if (!tmp)
			return (NULL);
		ft_envi_add_back(&dup, tmp);
		envi = envi->next;
	}
	return (dup);
}
