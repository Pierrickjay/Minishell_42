/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:28:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// check the key of the variable is valid
static int	ft_export_ident(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (len >= 1 && str[len - 1] == '+')
		len--;
	if (ft_all_isalnum_len(str, len) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// export a variable
static int	ft_export_set(t_shell *shell, char *key, char *value, int type)
{
	t_envi		*new;

	if (ft_getenvi(key, shell->envi) != NULL)
	{
		shell->envi = ft_envi_update_value(key, value, type, shell->envi);
		if (shell->envi == FAIL)
			return (EXIT_FAILURE);
		free(key);
		free(value);
	}
	else
	{
		new = ft_envi_new(key, value, type);
		if (!new)
			return (EXIT_FAILURE);
		ft_envi_add_back(&(shell->envi), new);
	}
	return (EXIT_SUCCESS);
}

//cat the export value
static int	ft_export_cat(t_shell *shell, char *key, char *value, int type)
{
	char	*tmp;
	char	*new_value;
	size_t	len;

	len = ft_strlen(key);
	if (key[len - 1] == '+')
		key[len - 1] = '\0';
	if (ft_getenvi(key, shell->envi) != NULL)
	{
		tmp = ft_getenvi(key, shell->envi);
		new_value = ft_strjoin(tmp, value);
		if (!value)
			return (EXIT_FAILURE);
		free(value);
		if (ft_export_set(shell, key, new_value, type) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_export_set(shell, key, value, type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// create a new enviroment variable
static int	ft_export_create(t_shell *shell, char *arg)
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
	if (cat && ft_export_cat(shell, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (111)"), 1);
	else if (!cat && ft_export_set(shell, key, value, type))
		return (free(value), free(key), ft_msg_malloc("export.c (115)"), 1);
	return (EXIT_SUCCESS);
}

// export builtin function return the exit code
int	ft_export(t_shell *shell)
{
	const char	**args = (const char **)shell->args[shell->id_child];
	int			i;

	if (args[1] == NULL)
		return (FAILURE);
	i = 0;
	while (args[++i])
	{
		if (ft_var_special(args[i][0]) || ft_export_ident((char *)args[i]))
		{
			ft_msg_builtins("export", (char *)args[i], IDENT);
			shell->status = 1;
			continue ;
		}
		if (ft_export_create(shell, (char *)args[i]))
			return (EXIT_FAILURE);
		if (shell->env)
			ft_free_strs(shell->env);
		shell->env = ft_envi_to_env(shell->envi);
		if (shell->env == FAIL)
			return (EXIT_FAILURE);
	}
	if (shell->status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
