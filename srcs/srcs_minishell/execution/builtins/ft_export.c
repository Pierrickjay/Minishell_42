/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 12:25:07 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	ft_export_bis(t_exec *exec, char *key, char *value)
{
	t_envi		*new;

	if (ft_getenvi(key, exec->envi) != NULL)
	{
		exec->envi = ft_envi_update_value(key, value, exec->envi);
		if (!exec->envi)
			return (EXIT_FAILURE);
		free(key);
		free(value);
	}
	else
	{
		new = ft_envi_new(key, value, NORMAL);
		if (!new)
			return (EXIT_FAILURE);
		ft_envi_add_back(&(exec->envi), new);
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	char		*key;
	char		*value;

	if (args[1] == NULL)
		return (ft_envi_print(exec->envi), EXIT_SUCCESS);
	key = ft_get_key((char *)args[1]);
	value = ft_get_value((char *)args[1]);
	if (!key || !value)
		return (EXIT_FAILURE);
	if (ft_isalpha(key[0]) == 0)
		return (free(key), free(value), EXIT_FAILURE);
	if (ft_export_bis(exec, key, value))
		return (EXIT_FAILURE);
	ft_free_strs(exec->env);
	exec->env = ft_envi_to_env(exec->envi);
	if (!exec->env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
