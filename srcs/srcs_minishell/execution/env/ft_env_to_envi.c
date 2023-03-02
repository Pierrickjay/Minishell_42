/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_envi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:52:12 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 12:43:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_envi	*ft_env_to_envi(char **env)
{
	t_envi	*envi;
	t_envi	*new;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	envi = NULL;
	while (env[i])
	{
		key = ft_get_key(env[i]);
		value = ft_get_value(env[i]);
		if (!key || !value)
			return (ft_free_envi(envi), NULL);
		new = ft_envi_new(key, value);
		if (!new)
			return (ft_free_envi(envi), NULL);
		ft_envi_add_back(&envi, new);
		i++;
	}
	return (envi);
}
