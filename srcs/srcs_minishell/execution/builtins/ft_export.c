/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 17:28:12 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_export(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	char		*key;
	char		*value;
	t_envi		*new;

	if (args[1] == NULL)
		return (EXIT_FAILURE);
	key = ft_get_key((char *)args[1]);
	value = ft_get_value((char *)args[1]);
	if (!key || !value)
		return (EXIT_FAILURE);
	if (ft_isalpha(key[0]) == 0)
		return (free(key), free(value), EXIT_FAILURE);
	new = ft_envi_new(key, value);
	if (!new)
		return (EXIT_FAILURE);
	ft_free_strs(exec->env);
	exec->envi = ft_unset_bis(key, exec->envi);
	ft_envi_add_back(&(exec->envi), new);
	exec->env = ft_envi_to_env(exec->envi);
	if (!exec->env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
