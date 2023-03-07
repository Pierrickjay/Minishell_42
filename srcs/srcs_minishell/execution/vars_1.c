/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 17:52:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// get the value of a variable and split it each time there is a space
static int	ft_lst_split_vars(t_list *tmp)
{
	char	**strs;
	t_list	*new;
	t_list	*args;
	char	*str;
	int		i;

	strs = ft_split(tmp->content, ' ');
	if (!strs)
		return (EXIT_FAILURE);
	free(tmp->content);
	tmp->content = strs[0];
	if (!tmp->content)
		return (EXIT_FAILURE);
	args = NULL;
	i = 1;
	while (strs[i])
	{
		str = strs[i++];
		new = ft_lstnew(str, ARG);
		if (!new)
			return (EXIT_FAILURE);
		ft_lstadd_back(&args, new);
	}
	return (ft_lstadd(&tmp, args), free(strs), EXIT_SUCCESS);
}

// update lst content for a type VAR
static int	ft_get_var_type(t_exec *exec, t_list *lst, int prev, int ec)
{
	size_t	len;
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
	len = ft_strlen(value);
	if (value[len - 1] == ' ')
		value[len - 1] = '\0';
	if (ft_strchr(value, ' '))
	{
		if (ft_lst_split_vars(lst))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	*ft_check_var(t_exec *exec, char *vars, int ec, \
							const size_t size)
{
	char	*str;
	t_list	*to_join;

	str = NULL;
	to_join = NULL;
	exec->exit_code = ec;
	if (vars[0] == '$' && ft_all_isalnum(&vars[1]))
	{
		str = ft_strdup(ft_getenvi(&vars[1], exec->envi));
		if (!str)
			return (ft_strdup(""));
		return (str);
	}
	vars = ft_check_vars(exec, (const size_t) size, &to_join, vars);
	if (vars[0] == '$' && ft_getenvi(&vars[1], exec->envi))
	{
		str = ft_strdup(ft_getenvi(&vars[1], exec->envi));
		if (!str)
			return (ft_strdup(""));
		ft_lstadd_front(&to_join, ft_lstnew(str, -1));
	}
	else
		ft_lstadd_front(&to_join, ft_lstnew(ft_strdup(vars), -1));
	str = ft_lstjoin(to_join);
	return (ft_free_lst(to_join), str);
}

// update lst content for a lot of vars
static int	ft_get_var_str(t_exec *exec, t_list *lst, int prev, int ec)
{
	const size_t	size = ft_envi_size(exec->envi);
	char			*tmp;
	t_list			*to_join;
	size_t			i;
	char			**vars;

	to_join = NULL;
	lst->content = ft_content_update(lst->content);
	if (!lst->content)
		return (EXIT_FAILURE);
	vars = ft_split(lst->content, ' ');
	if (!vars)
		return (EXIT_FAILURE);
	i = 0;
	while (vars[i])
	{
		tmp = ft_check_var(exec, vars[i], ec, size);
		if (!tmp)
			return (EXIT_FAILURE);
		ft_lstadd_back(&to_join, ft_lstnew(tmp, -1));
		i++;
	}
	if (ft_update_lst(lst, to_join, &prev) || ft_lst_split_vars(lst))
		return (EXIT_FAILURE);
	return (ft_free_lst(to_join), ft_free_strs(vars), EXIT_SUCCESS);
}

// parsing VAR
int	ft_get_vars(t_exec *exec, int exit_code)
{
	t_list	*lst;
	size_t	n;
	int		previous;

	previous = -1;
	lst = exec->lst;
	while (exec->envi && lst)
	{
		n = ft_nb_var(lst->content);
		if (n == 1 && lst->type == VAR && ft_all_isalnum(&lst->content[1]))
		{
			if (ft_get_var_type(exec, lst, previous, exit_code))
				return (EXIT_FAILURE);
		}
		else if (n >= 1 && ft_strchr(lst->content, '$') != NULL)
		{
			if (ft_strchr(lst->content, '=') != NULL)
				;
			else if (ft_get_var_str(exec, lst, previous, exit_code))
				return (EXIT_FAILURE);
		}
		previous = lst->type;
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
