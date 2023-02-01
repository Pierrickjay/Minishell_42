/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:36:07 by pjay              #+#    #+#             */
/*   Updated: 2023/02/01 10:53:46 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*in;

	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			in = ft_lstlast(*lst);
			in->next = new;
		}
		else
			*lst = new;
	}
}
