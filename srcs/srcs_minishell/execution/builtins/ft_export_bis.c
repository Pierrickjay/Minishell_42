/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:28:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 08:36:12 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_set(char *arg, int *type, int *var_exist)
{
	if (ft_strchr(arg, '=') == NULL)
		*type = NO_VALUE;
	if (ft_strchr(arg, '$') != NULL)
		*var_exist = true;
}

int	ft_export_cat(t_exec *exec, char *key, char *value, int type)
{
	char	*tmp;
	char	*new_value;
	size_t	len;

	len = ft_strlen(key);
	if (key[len - 1] == '+')
		key[len - 1] = '\0';
	tmp = ft_getenvi(key, exec->envi);
	if (!tmp)
		return (EXIT_FAILURE);
	new_value = ft_strjoin(tmp, value);
	if (!value)
		return (EXIT_FAILURE);
	free(value);
	if (ft_export_set(exec, key, new_value, type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_is_ident(int c)
{
	if (ft_isdigit(c) || c == '?' || c == '!' || c == '@' || c == '#')
		return (true);
	return (false);
}
