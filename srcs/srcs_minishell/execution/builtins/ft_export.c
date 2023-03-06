/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 18:16:22 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// export a variable
int	ft_export_set(t_exec *exec, char *key, char *value, int type)
{
	t_envi		*new;

	if (ft_getenvi(key, exec->envi) != NULL)
	{
		exec->envi = ft_envi_update_value(key, value, type, exec->envi);
		if (exec->envi == FAIL)
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
	int		var_exist;
	int		cat;
	char	*key;
	char	*value;
	int		type;

	cat = false;
	var_exist = false;
	type = NORMAL;
	ft_set(arg, &type, &var_exist);
	key = ft_get_key(arg);
	value = ft_get_value(arg);
	if (!key || !value)
		return (ft_msg_malloc("export.c (109)"), EXIT_FAILURE);
	if (ft_check_last_char(key, '+'))
		cat = true;
	if (cat && ft_export_cat(exec, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (111)"), 1);
	if (var_exist && ft_export_set_var(exec, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (113)"), 1);
	else if (!cat && !var_exist && ft_export_set(exec, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (115)"), 1);
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
		if (ft_is_ident(args[i][0]))
		{
			ft_msg_builtins("export", (char *)args[i], IDENT);
			exec->status = 1;
			continue ;
		}
		if (ft_export_create(exec, (char *)args[i]))
			return (EXIT_FAILURE);
		if (exec->env)
			ft_free_strs(exec->env);
		exec->env = ft_envi_to_env(exec->envi);
		if (exec->env == FAIL)
			return (EXIT_FAILURE);
	}
	if (exec->status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
