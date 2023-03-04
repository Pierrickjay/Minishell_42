/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 16:52:01 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	ft_export_set(t_exec *exec, char *key, char *value, int type)
{
	t_envi		*new;

	if (ft_getenvi(key, exec->envi) != NULL)
	{
		exec->envi = ft_envi_update_value(key, value, type, exec->envi);
		if (!exec->envi)
			return (EXIT_FAILURE);
		free(key);
		free(value);
	}
	else
	{
		new = ft_envi_new(key, value, type);
		if (!new)
			return (EXIT_FAILURE);
		ft_envi_add_back(&(exec->envi), new);
	}
	return (EXIT_SUCCESS);
}

static int	ft_export_create(t_exec *exec, char *arg)
{
	char		*key;
	char		*value;
	int			type;

	type = NORMAL;
	if (ft_strchr(arg, '=') == NULL)
		type = NO_VALUE;
	key = ft_get_key(arg);
	value = ft_get_value(arg);
	if (!key || !value)
		return (ft_msg(NULL, NULL, MA, NULL), EXIT_FAILURE);
	if (ft_export_set(exec, key, value, type))
		return (ft_msg(NULL, NULL, MA, NULL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_export(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	int			i;

	if (args[1] == NULL)
		return (ft_envi_print(exec->envi), EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]))
		{
			ft_msg(NULL, (char *)args[i], EXP1, NULL);
			i++;
			continue ;
		}
		if (ft_export_create(exec, (char *)args[i]))
			return (EXIT_FAILURE);
		ft_free_strs(exec->env);
		exec->env = ft_envi_to_env(exec->envi);
		if (!exec->env)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
