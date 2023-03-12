/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:41:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/12 10:59:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	ft_add_pwd(t_envi **envi)
{
	t_envi	*new;
	char	*key;
	char	*value;

	key = ft_strdup("PWD");
	if (!key)
		return (EXIT_FAILURE);
	value = getcwd(NULL, 0);
	if (!value)
		return (free(key), EXIT_FAILURE);
	new = ft_envi_new(key, value, NORMAL);
	if (!new)
		return (free(key), free(value), EXIT_FAILURE);
	ft_envi_add_back(envi, new);
	return (EXIT_SUCCESS);
}

static int	ft_add_shlvl(t_envi **envi)
{
	t_envi	*new;
	char	*key;
	char	*value;

	key = ft_strdup("SHLVL");
	if (!key)
		return (EXIT_FAILURE);
	value = ft_strdup("0");
	if (!value)
		return (free(key), EXIT_FAILURE);
	new = ft_envi_new(key, value, NORMAL);
	if (!new)
		return (free(key), free(value), EXIT_FAILURE);
	ft_envi_add_back(envi, new);
	return (EXIT_SUCCESS);
}

static int	ft_add_underscore(t_envi **envi)
{
	t_envi	*new;
	char	*key;
	char	*value;

	key = ft_strdup("_");
	if (!key)
		return (EXIT_FAILURE);
	value = ft_strdup("/usr/bin/env");
	if (!value)
		return (free(key), EXIT_FAILURE);
	new = ft_envi_new(key, value, NORMAL);
	if (!new)
		return (free(key), free(value), EXIT_FAILURE);
	ft_envi_add_back(envi, new);
	return (EXIT_SUCCESS);
}

t_envi	*ft_envi_null(t_envi *envi)
{
	if (ft_add_pwd(&envi) == EXIT_FAILURE)
		return (NULL);
	if (ft_add_shlvl(&envi) == EXIT_FAILURE)
		return (ft_free_envi(envi), NULL);
	if (ft_add_underscore(&envi) == EXIT_FAILURE)
		return (ft_free_envi(envi), NULL);
	return (envi);
}
