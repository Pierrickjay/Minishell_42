/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 14:11:40 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_list	*ft_get_vars(t_list *lst)
{
	t_list	*tmp;
	char	*value;

	tmp = lst;
	while (lst)
	{
		if (lst->type == VAR)
		{
			value = getenv(&(lst->content[1]));
			if (value)
			{
				free(lst->content);
				lst->content = ft_strdup(value);
				if (!lst->content)
					return (NULL);
				lst->type = ARG;
			}
		}
		lst = lst->next;
	}
	lst = tmp;
	return (lst);
}
