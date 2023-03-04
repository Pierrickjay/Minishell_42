/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 10:43:01 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_lst_split_vars(t_list *tmp, char **strs)
{
	t_list	*new;
	char	*str;
	int		i;

	tmp->content = ft_strdup(strs[0]);
	if (!tmp->content)
		return (EXIT_FAILURE);
	i = 1;
	while (strs[i])
	{
		str = ft_strdup(strs[i]);
		if (!str)
			return (EXIT_FAILURE);
		new = ft_lstnew(str, ARG);
		if (!new)
			return (EXIT_FAILURE);
		ft_lstadd(new, &tmp);
		i++;
	}
	ft_free_strs(strs);
	return (EXIT_SUCCESS);
}

static int	ft_vars_replace(t_list *tmp, char *value, int previous)
{
	char	**strs;

	free(tmp->content);
	tmp->content = ft_strdup(value);
	if (!tmp->content)
		return (EXIT_FAILURE);
	if (previous == -1 || previous == PIPE || previous == FILES)
		tmp->type = CMD;
	else
		tmp->type = ARG;
	if (ft_strchr(value, ' '))
	{
		strs = ft_split(tmp->content, ' ');
		if (!strs)
			return (EXIT_FAILURE);
		free(tmp->content);
		if (ft_lst_split_vars(tmp, strs))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_exitcode(t_list *tmp, int exit_code, int previous)
{
	char	*str_exit_code;

	free(tmp->content);
	str_exit_code = ft_itoa(exit_code);
	if (!str_exit_code)
		return (EXIT_FAILURE);
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
