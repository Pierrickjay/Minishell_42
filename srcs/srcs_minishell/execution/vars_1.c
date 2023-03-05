/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 12:45:15 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_lst_split_vars(t_list *tmp, char **strs)
{
	t_list	*new;
	t_list	*args;
	char	*str;
	int		i;

	tmp->content = ft_strdup(strs[0]);
	if (!tmp->content)
		return (EXIT_FAILURE);
	args = NULL;
	i = 1;
	while (strs[i])
	{
		str = ft_strdup(strs[i]);
		if (!str)
			return (EXIT_FAILURE);
		new = ft_lstnew(str, ARG);
		if (!new)
			return (EXIT_FAILURE);
		ft_lstadd_back(&args, new);
		i++;
	}
	ft_lstadd(&tmp, args);
	ft_free_strs(strs);
	return (EXIT_SUCCESS);
}

static int	ft_get_var_type(t_exec *exec, t_list *lst, int prev, int ec)
{
	char	**strs;
	char	*value;

	if (ft_strcmp("$?", lst->content) == 0)
	{
		if (ft_set_exit_code(lst, ec, prev, true))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	value = ft_strdup(ft_getenvi(&lst->content[1], exec->envi));
	if (!value)
		return (EXIT_FAILURE);
	free(lst->content);
	lst->content = value;
	lst->type = ft_get_type_var(&prev);
	if (ft_strchr(value, ' '))
	{
		strs = ft_split(lst->content, ' ');
		if (!strs)
			return (EXIT_FAILURE);
		free(lst->content);
		if (ft_lst_split_vars(lst, strs))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_get_var_str(t_exec *exec, t_list *lst, int prev, int ec)
{
	t_list		*new_lst;
	char		**vars;
	char		*value;
	int			i;

	if (ft_strchr(lst->content, '=') != NULL)
		return (EXIT_SUCCESS);
	new_lst = NULL;
	vars = ft_split(lst->content, '$');
	if (!vars || ft_update_lst(&lst))
		return (EXIT_FAILURE);
	i = -1;
	while (vars[++i])
	{
		if (ft_strcmp("?", vars[i]) == 0 && ft_set_exit_code(lst, ec, prev, 0))
		{
			i++;
			continue ;
		}
		value = ft_strdup(ft_getenvi(vars[i], exec->envi));
		if (!value)
			return (ft_free_strs(vars), EXIT_FAILURE);
		ft_lstadd_back(&new_lst, ft_lstnew(value, ft_get_type_var(&prev)));
	}
	return (ft_free_strs(vars), ft_lstadd(&lst, new_lst), EXIT_SUCCESS);
}

int	ft_get_vars(t_exec *exec, int exit_code)
{
	t_list	*lst;
	size_t	n;
	int		previous;

	previous = -1;
	lst = exec->lst;
	while (lst)
	{
		n = ft_nb_var(lst->content);
		if (n == 1 && lst->type == VAR)
		{
			if (ft_get_var_type(exec, lst, previous, exit_code) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (n >= 1 && ft_strchr(lst->content, '$') != NULL)
		{
			if (ft_get_var_str(exec, lst, previous, exit_code) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		previous = lst->type;
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
