/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 20:23:19 by obouhlel         ###   ########.fr       */
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

static int	ft_exitcode(t_list *tmp, int exit_code, int previous)
{
	char	*str_exit_code;

	str_exit_code = ft_itoa(exit_code);
	if (!str_exit_code)
		return (EXIT_FAILURE);
	free(tmp->content);
	tmp->content = str_exit_code;
	if (previous == -1 || previous == PIPE || previous == FILES)
		tmp->type = CMD;
	else
		tmp->type = ARG;
	return (EXIT_SUCCESS);
}

int	ft_get_vars(t_exec *exec, int ec)
{
	t_list	*tmp;
	int		prev;
	char	*value;

	tmp = exec->lst;
	prev = -1;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			if (!ft_strcmp("$?", tmp->content) && ft_exitcode(tmp, ec, prev))
				return (EXIT_FAILURE);
			else
			{
				value = ft_getenvi(&(tmp->content[1]), exec->envi);
				if (value && ft_vars_replace(tmp, value, prev))
					return (EXIT_FAILURE);
			}
		}
		prev = tmp->type;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
