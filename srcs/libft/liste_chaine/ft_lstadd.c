/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:39:00 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 11:15:04 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstadd(t_list **list, t_list *new_list)
{
	t_list	*last;
	t_list	*tmp;

	tmp = NULL;
	if ((*list)->next != NULL)
	{
		if ((*list)->next->next)
			tmp = (*list)->next->next;
		else
		{
			ft_lstadd_back(list, new_list);
			return ;
		}
		(*list)->next = new_list;
		last = ft_lstlast(new_list);
		last->next = tmp;
	}
	else
		ft_lstadd_back(list, new_list);
}
