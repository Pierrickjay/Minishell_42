/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_envi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:52:12 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:28:58 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// convert a char **env to a t_envi *envi
t_envi	*ft_env_to_envi(char **env)
{
	t_envi	*envi;
	t_envi	*new;
	char	*key;
	char	*value;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	envi = NULL;
	while (env[i])
	{
		key = ft_get_key(env[i]);
		value = ft_get_value(env[i]);
		if (!key || !value)
			return (ft_free_envi(envi), FAIL);
		new = ft_envi_new(key, value, NORMAL);
		if (!new)
			return (ft_free_envi(envi), FAIL);
		ft_envi_add_back(&envi, new);
		i++;
	}
	return (envi);
}
