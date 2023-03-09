/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 13:44:21 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// ec it's for the exit code, because exit_code it's to long

// the main get var, to update
int	ft_get_vars(t_envi *envi, t_list *lst, int exit_code)
{
	size_t	n;
	int		previous;

	previous = -1;
	while (envi && lst)
	{
		n = ft_nb_var(lst->content);
		if (n >= 1 && lst->content[1] && lst->type != REDIR && \
				ft_update_str_var(envi, lst, previous, exit_code))
			return (EXIT_FAILURE);
		previous = lst->type;
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

// when we have a string with a var
int	ft_update_str_var(t_envi *envi, t_list *lst, int prev, int ec)
{
	const size_t	size = ft_envi_size(envi);
	char			*tmp;
	t_list			*to_join;
	size_t			i;
	char			**vars;

	to_join = NULL;
	lst->content = ft_content_update(lst->content);
	if (!lst->content)
		return (EXIT_FAILURE);
	vars = ft_split(lst->content, '|');
	if (!vars)
		return (EXIT_FAILURE);
	i = 0;
	while (vars[i])
	{
		tmp = ft_check_var_1(envi, vars[i], ec, (size_t)size);
		if (!tmp)
			return (ft_free_strs(vars), EXIT_FAILURE);
		ft_lstadd_back(&to_join, ft_lstnew(tmp, -1));
		i++;
	}
	if (ft_update_lst(lst, to_join, &prev))
		return (EXIT_FAILURE);
	return (ft_free_lst(to_join), ft_free_strs(vars), EXIT_SUCCESS);
}

char	*ft_check_var_1(t_envi *envi, char *vars, int ec, size_t size)
{
	char	*str;
	t_list	*to_join;

	str = NULL;
	to_join = NULL;
	if (vars[0] != '$')
		ft_lstadd_front(&to_join, ft_lstnew(ft_strdup(vars), -1));
	if (vars[0] == '$' && ft_all_isalnum(&vars[1]))
	{
		str = ft_check_envi(&vars[1], envi);
		if (!str)
			return (NULL);
		return (str);
	}
	vars = ft_check_var_2(envi, (const size_t) size, &to_join, vars);
	if (ft_check_var_3(vars, &to_join, ec))
		return (NULL);
	str = ft_lstjoin(to_join);
	return (ft_free_lst(to_join), str);
}

// save a char after the var in list to join,
// and return var with just a alphanum
char	*ft_check_var_2(t_envi *envi, size_t size, t_list **to_join, char *var)
{
	size_t	len;
	char	*add;
	size_t	i;

	i = 0;
	len = ft_strlen(var);
	while (var[0] == '$' && !ft_all_isalnum(&var[1]) && len-- && i < size)
	{
		if (len == 1 && ft_var_special(var[1]))
			break ;
		add = ft_strdup(&var[len]);
		if (!add)
			return (NULL);
		var[len] = '\0';
		ft_lstadd_front(to_join, ft_lstnew(add, -1));
		i++;
	}
	if (!ft_var_special(var[1]))
	{
		add = ft_check_envi(&var[1], envi);
		if (!add)
			return (NULL);
		ft_lstadd_front(to_join, ft_lstnew(add, -1));
	}
	return (var);
}

// for var special example $1, $$ etc..
int	ft_check_var_3(char *var, t_list **to_join, int exit_code)
{
	char	*add;

	add = NULL;
	if (!ft_strcmp("$?", var))
	{
		add = ft_itoa(exit_code);
		if (!add)
			return (EXIT_FAILURE);
		ft_lstadd_front(to_join, ft_lstnew(add, -1));
	}
	ft_bzero(var, ft_strlen(var));
	return (EXIT_SUCCESS);
}
