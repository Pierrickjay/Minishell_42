/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:55 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/12 11:08:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// free one env variable and relink the list
static t_envi	*ft_unset_bis_bis(t_envi *envi, t_envi *tmp, t_envi *top)
{
	if (tmp == NULL)
	{
		tmp = envi;
		envi = envi->next;
		ft_free_envi_delone(tmp);
		return (envi);
	}
	else if (tmp && envi->next == NULL)
	{
		tmp->next = NULL;
		ft_free_envi_delone(envi);
		return (top);
	}
	else
	{
		tmp->next = envi->next;
		ft_free_envi_delone(envi);
		return (top);
	}
	return (top);
}

// unset a variable
t_envi	*ft_unset_bis(const char *name, t_envi *envi)
{
	t_envi	*tmp;
	t_envi	*top;

	tmp = NULL;
	top = envi;
	while (envi)
	{
		if (ft_strcmp(name, "_") == 0)
			return (top);
		else if (ft_strcmp(name, envi->key) == 0)
			return (ft_unset_bis_bis(envi, tmp, top));
		tmp = envi;
		envi = envi->next;
	}
	return (top);
}

// unset a variable
int	ft_unset(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	int			i;

	if (args[1] == NULL)
		return (EXIT_SUCCESS);
	ft_free_strs(exec->env);
	i = 0;
	while (args[i])
		exec->envi = ft_unset_bis(args[i++], exec->envi);
	exec->env = ft_envi_to_env(exec->envi);
	if (exec->env == FAIL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
