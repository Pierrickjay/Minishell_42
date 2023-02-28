/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 11:57:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_vars_replace(t_list *tmp, char *value, int previous)
{
	tmp->content = ft_strdup(value);
	if (!tmp->content)
		return (EXIT_FAILURE);
	free(tmp->content);
	if (previous == -1 || previous == PIPE || previous == FILES)
		tmp->type = CMD;
	else
		tmp->type = ARG;
	return (EXIT_SUCCESS);
}

int	ft_get_vars(t_exec *exec)
{
	t_list	*tmp;
	int		previous;
	char	*value;

	tmp = exec->lst;
	previous = -1;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			value = ft_getenvi(&(tmp->content[1]), exec->envi);
			if (value)
				if (ft_vars_replace(tmp, value, previous) == EXIT_FAILURE)
					return (EXIT_FAILURE);
		}
		previous = tmp->type;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
