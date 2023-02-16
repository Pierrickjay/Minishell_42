/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:54:24 by pjay              #+#    #+#             */
/*   Updated: 2023/02/16 12:04:25 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_list	*ft_fill(char *str, t_free *free)
{
	int		i;
	t_list	*list;
	t_list	*tmp;

	tmp = NULL;
	list = NULL;
	i = 1;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	free->split = trim_all(ft_split(str, ' '));
	list->content = free->split[0];
	while (free->split[i])
	{
		tmp = ft_lstnew(free->split[i], -1);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	ft_set_type(list);
	//show_list(list);
	return (list);
}
