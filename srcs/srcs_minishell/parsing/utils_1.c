/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 15:31:46 by pjay             ###   ########.fr       */
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
	free->split = ft_split(str, ' ');
	list->content = free->split[0];
	while (free->split[i])
	{
		tmp = ft_lstnew(free->split[i]);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	//show_list(list);
	// free_split(to_free.split);
	return (list);
}
