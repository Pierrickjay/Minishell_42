/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:54:24 by pjay              #+#    #+#             */
/*   Updated: 2023/03/10 12:38:55 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	*ft_erase_all(char **str_dup, t_list *list, char *str)
{
	if (str_dup)
	{
		ft_putendl_fd("syntaxe error", 2);
		ft_free_strs(str_dup);
	}
	free(list);
	free(str);
	return (NULL);
}

t_list	*ft_fill_2(t_free *to_free, t_list *list)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	list->content = to_free->newsplit[0];
	list->not_expend = to_free->not_expend[0];
	if (to_free->is_in_quote[0] == true)
		list->type = ARG;
	else
		list->type = -1;
	while (to_free->newsplit[i])
	{
		tmp = ft_lstnew_spe(to_free->newsplit[i], \
			-1, to_free->not_expend[i], to_free->is_in_quote[i]);
		if (tmp == NULL)
			return (NULL);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	ft_set_type(list);
	return (list);
}

t_list	*ft_fill(char *str, t_free *to_free)
{
	t_list	*list;
	char	**str_dup;
	char	*new_str;

	if (count_quote_single(str) == -1)
		return (free_str_quote_error(str));
	new_str = new_string(str);
	if (!new_str)
		return (free(str), NULL);
	list = NULL;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	str_dup = split_parsing(new_str, ' ');
	if (!str_dup)
		return (ft_erase_all(str_dup, list, str));
	if (trim_all(str_dup, to_free) == -1)
		return (ft_free_lst(list),
			ft_free_strs(str_dup), free(str), free(new_str), NULL);
	list = ft_fill_2(to_free, list);
	if (!list)
		return (NULL);
	return (free(new_str), list);
}
