/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 10:47:22 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_export(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	char		*key;
	char		*value;
	t_envi		*new;
	size_t		len;

	if (args[1] == NULL)
		return (EXIT_FAILURE);
	len = 0;
	while (args[1][len] && args[1][len] != '=')
		len++;
	key = ft_substr(args[1], 0, len);
	if (!key)
		return (EXIT_FAILURE);
	value = ft_substr(args[1], len + 1, ft_strlen(args[1]));
	if (!value)
		return (EXIT_FAILURE);
	new = ft_envi_new(key, value);
	if (!new)
		return (EXIT_FAILURE);
	ft_free_strs(exec->env);
	ft_envi_add_back(&(exec->envi), new);
	exec->env = ft_envi_to_env(exec->envi);
	if (!exec->env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
