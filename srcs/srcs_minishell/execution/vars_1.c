/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 12:15:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// ec it's for the exit code, because exit_code it's to long

// the main get var, to update
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
		if (n == 1 && lst->type == VAR && lst->content[1] && \
		!ft_var_special(lst->content[1]) && ft_all_isalnum(&lst->content[1]) \
		&& ft_only_one_var(exec, lst, previous, exit_code))
			return (EXIT_FAILURE);
		else if (n == 1 && lst->type == VAR && !ft_strcmp("$", lst->content))
			lst->type = ARG;
		else if (n >= 1 && lst->content[1] && \
				ft_update_str_var(exec, lst, previous, exit_code))
			return (EXIT_FAILURE);
		previous = lst->type;
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

// when i have just only one dolars, and a good var
int	ft_only_one_var(t_exec *exec, t_list *lst, int prev, int ec)
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

// when we have a string with a var
int	ft_update_str_var(t_exec *exec, t_list *lst, int prev, int ec)
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
		tmp = ft_check_var_1(exec, vars[i], ec, (size_t)size);
		if (!tmp)
			return (EXIT_FAILURE);
		ft_lstadd_back(&to_join, ft_lstnew(tmp, -1));
		i++;
	}
	if (ft_update_lst(lst, to_join, &prev) || ft_lst_split_vars(lst))
		return (EXIT_FAILURE);
	return (ft_free_lst(to_join), ft_free_strs(vars), EXIT_SUCCESS);
}

char	*ft_check_var_1(t_exec *exec, char *vars, int ec, size_t size)
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
	vars = ft_check_var_2(exec, (const size_t) size, &to_join, vars);
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

// save a char after the var in list to join,
// and return var with just a alphanum
char	*ft_check_var_2(t_exec *exec, size_t size, t_list **to_join, char *var)
{
	size_t	len;
	char	*add;
	size_t	i;

	i = 0;
	len = ft_strlen(var);
	while (var[0] == '$' && !ft_all_isalnum(&var[1]) && len-- && i < size)
	{
		if (len == 1 && ft_var_special(var[1]))
		{
			if (ft_check_var_3(var, to_join, exec->exit_code))
				return (NULL);
			break ;
		}
		add = ft_strdup(&var[len]);
		if (!add)
			return (NULL);
		var[len] = '\0';
		ft_lstadd_front(to_join, ft_lstnew(add, -1));
		i++;
	}
	return (var);
}
