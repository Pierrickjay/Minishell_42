/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:39:00 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 10:41:26 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstadd(t_list *new, t_list **previous)
{
	t_list	*tmp;

	tmp = (*previous)->next;
	(*previous)->next = new;
	new->next = tmp;
}
