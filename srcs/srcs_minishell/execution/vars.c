/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 12:46:17 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_get_vars(t_list **lst)
{
	t_list	*tmp;
	char	*value;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			value = getenv(&(tmp->content[1]));
			if (!value)
				ft_putendl_fd("VAR NOT FOUND", 2);
			if (value)
			{
				free(tmp->content);
				tmp->content = ft_strdup(value);
				if (!tmp->content)
					ft_putendl_fd("MALLOC FAIL", 2);
				tmp->type = ARG;
			}
		}
		tmp = tmp->next;
	}
}
