/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:54:24 by pjay              #+#    #+#             */
/*   Updated: 2023/02/21 15:10:23 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		ft_lstadd_back(&list, tmp);
		i++;
	}
	ft_set_type(list);
	return (list);
}

t_list	*ft_fill(char *str, t_free *to_free)
{
	t_list	*list;

	list = NULL;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	to_free->split = trim_all(ft_split(str, ' '));
	if (!(to_free->split[0]))
	{
		free(list);
		return (NULL);
	}
	return (ft_fill_2(to_free, list));
}
