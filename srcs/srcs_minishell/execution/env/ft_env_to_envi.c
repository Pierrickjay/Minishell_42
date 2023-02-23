/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_envi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:52:12 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 11:33:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static char	*ft_get_key(char *env)
{
	int		len;
	char	*key;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = ft_substr(env, 0, len);
	if (!key)
		return (NULL);
	return (key);
}

static char	*ft_get_value(char *env)
{
	int		len;
	char	*value;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	value = ft_substr(env, len + 1, ft_strlen(env) - len);
	if (!value)
		return (NULL);
	return (value);
}

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
