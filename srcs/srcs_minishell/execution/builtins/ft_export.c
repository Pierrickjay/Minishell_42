/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 19:17:30 by obouhlel         ###   ########.fr       */
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

//cat the export value
static int	ft_export_cat(t_exec *exec, char *key, char *value, int type)
{
	char	*tmp;
	char	*new_value;
	size_t	len;

	len = ft_strlen(key);
	if (key[len - 1] == '+')
		key[len - 1] = '\0';
	if (ft_getenvi(key, exec->envi) != NULL)
	{
		tmp = ft_getenvi(key, exec->envi);
		new_value = ft_strjoin(tmp, value);
		if (!value)
			return (EXIT_FAILURE);
		free(value);
		if (ft_export_set(exec, key, new_value, type) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_export_set(exec, key, value, type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// create a new enviroment variable
static int	ft_export_create(t_exec *exec, char *arg)
{
	int		cat;
	char	*key;
	char	*value;
	int		type;

	cat = false;
	type = NORMAL;
	if (ft_strchr(arg, '=') == NULL)
		type = NO_VALUE;
	key = ft_get_key(arg);
	value = ft_get_value(arg);
	if (!key || !value)
		return (ft_msg_malloc("export.c (109)"), EXIT_FAILURE);
	if (ft_check_last_char(key, '+'))
		cat = true;
	if (cat && ft_export_cat(exec, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (111)"), 1);
	else if (!cat && ft_export_set(exec, key, value, type))
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
		if (ft_var_special(args[i][0]))
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
