/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:54:24 by pjay              #+#    #+#             */
/*   Updated: 2023/03/07 08:59:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	*ft_erase_all(char **str_dup, t_list *list, char *str)
{
	if (str_dup)
	{
		ft_putendl_fd("synthaxe error", 2);
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
	list->content = to_free->split[0];
	while (to_free->split[i])
	{
		tmp = ft_lstnew(to_free->split[i], -1);
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
		return (NULL);
	list = NULL;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	str_dup = split_parsing(new_str, ' ');
	if (!str_dup)
		return (ft_erase_all(str_dup, list, str));
	to_free->split = trim_all(str_dup);
	if (!to_free->split || !(to_free->split[0]))
		return (ft_erase_all(str_dup, list, new_str));
	list = ft_fill_2(to_free, list);
	if (!list)
		return (NULL);
	return (free(new_str), list);
}
