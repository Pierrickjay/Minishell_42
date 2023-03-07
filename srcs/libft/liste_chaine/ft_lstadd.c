/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:39:00 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 17:43:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstadd(t_list **list, t_list *new_list)
{
	t_list	*last;
	t_list	*tmp;

	if (!(*list)->next)
	{
		tmp = NULL;
		if ((*list)->next && (*list)->next->next)
			tmp = (*list)->next->next;
		(*list)->next = new_list;
		last = ft_lstlast(new_list);
		last->next = tmp;
	}
	else
		ft_lstadd_back(list, new_list);
}
