/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:34:47 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 19:11:23 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// the expend for list
int	ft_lst_expend(t_envi *envi, t_list *lst, int exit_code)
{
	char	*tmp;

	while (envi && lst)
	{
		if (ft_strchr(lst->content, '$') \
			&& lst->not_expend == false && lst->type != FILES)
		{
			tmp = lst->content;
			lst->content = ft_expend(envi, tmp, exit_code);
			if (!lst->content)
				return (EXIT_FAILURE);
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

// the main of expend
char	*ft_expend(t_envi *envi, char *content, int exit_code)
{
	char			*tmp;
	t_list			*to_join;
	int				i;
	char			**vars;

	to_join = NULL;
	tmp = ft_content_update(content);
	if (!tmp)
		return (NULL);
	vars = ft_split(tmp, -1);
	if (!vars)
		return (NULL);
	ft_free((void **)&tmp);
	i = -1;
	while (vars[++i])
	{
		tmp = ft_expend_bis(envi, vars[i], exit_code);
		if (!tmp)
			return (ft_free_strs(vars), ft_free_lst(to_join), NULL);
		ft_lstadd_back(&to_join, ft_lstnew(tmp, -1));
	}
	content = ft_lstjoin(to_join);
	if (!content)
		return (ft_free_lst(to_join), ft_free_strs(vars), NULL);
	return (ft_free_lst(to_join), ft_free_strs(vars), content);
}

// the expend for a variable
char	*ft_expend_bis(t_envi *envi, char *vars, int exit_code)
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
	vars = ft_expend_join(envi, &to_join, vars);
	if (ft_expend_exit_code(vars, &to_join, exit_code))
		return (NULL);
	str = ft_lstjoin(to_join);
	return (ft_free_lst(to_join), str);
}

// save a char after the var in list to join,
// and return var with just a alphanum
char	*ft_expend_join(t_envi *envi, t_list **to_join, char *var)
{
	size_t	len;
	char	*add;
	size_t	i;

	i = 0;
	len = ft_strlen(var);
	while (var[0] == '$' && !ft_all_isalnum(&var[1]) && len--)
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
int	ft_expend_exit_code(char *var, t_list **to_join, int exit_code)
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
