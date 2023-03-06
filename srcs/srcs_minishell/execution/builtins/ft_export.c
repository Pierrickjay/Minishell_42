/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 10:13:12 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// export a variable
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

// join the value of a variable with the value of another variable
static int	ft_export_join(t_exec *exec, char *key, char *value, int type)
{
	size_t	i;
	char	**vars;
	char	*tmp;

	vars = ft_split(value, ':');
	if (!vars)
		return (EXIT_FAILURE);
	free(value);
	i = 0;
	while (vars[i])
	{
		tmp = ft_getenvi(&vars[i][1], exec->envi);
		free(vars[i]);
		vars[i] = ft_strdup(tmp);
		if (!vars[i])
			return (ft_free_strs(vars), EXIT_FAILURE);
		i++;
	}
	value = ft_strjoin_all(vars, ':');
	if (!value)
		return (ft_free_strs(vars), EXIT_FAILURE);
	ft_free_strs(vars);
	if (ft_export_set(exec, key, value, type))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// set a new value to an existing variable
static int	ft_export_set_var(t_exec *exec, char *key, char *value, int type)
{
	size_t	nb;
	char	*tmp;

	nb = ft_nb_var(value);
	if (nb == 1)
	{
		tmp = value;
		value = ft_strdup(ft_getenvi(&tmp[1], exec->envi));
		if (!value)
			return (free(tmp), EXIT_FAILURE);
		free(tmp);
		if (ft_export_set(exec, key, value, type))
			return (free(tmp), EXIT_FAILURE);
	}
	else if (nb > 1 && ft_export_join(exec, key, value, type))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// create a new enviroment variable
static int	ft_export_create(t_exec *exec, char *arg)
{
	bool		var_exist;
	char		*key;
	char		*value;
	int			type;

	var_exist = false;
	type = NORMAL;
	if (ft_strchr(arg, '=') == NULL)
		type = NO_VALUE;
	if (ft_strchr(arg, '$') != NULL)
		var_exist = true;
	key = ft_get_key(arg);
	value = ft_get_value(arg);
	if (!key || !value)
		return (ft_msg_malloc("export.c (107)"), EXIT_FAILURE);
	if (var_exist && ft_export_set_var(exec, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (109)"), 1);
	else if (!var_exist && ft_export_set(exec, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (111)"), 1);
	return (EXIT_SUCCESS);
}

// export builtin function return the exit code
int	ft_export(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	int			i;

	if (args[1] == NULL)
		return (FAILURE);
	i = 0;
	while (args[++i])
	{
		if (ft_isdigit(args[i][0]))
		{
			ft_msg_builtins("export", (char *)args[i], IDENT);
			exec->status = 1;
			continue ;
		}
		if (ft_export_create(exec, (char *)args[i]))
			return (EXIT_FAILURE);
		ft_free_strs(exec->env);
		exec->env = ft_envi_to_env(exec->envi);
		if (!exec->env)
			return (EXIT_FAILURE);
	}
	if (exec->status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
