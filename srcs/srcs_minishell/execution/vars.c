/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:21:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 14:38:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_getenv(char *name, t_envi *envi)
{
	while (envi)
	{
		if (ft_strcmp(envi->key, name) == 0)
			return (envi->value);
		envi = envi->next;
	}
	return (NULL);
}

void	*ft_get_vars(t_exec *exec)
{
	t_list	*tmp;
	char	*value;

	tmp = exec->lst;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			value = ft_getenv(&(tmp->content[1]), exec->envi);
			if (value)
			{
				free(tmp->content);
				tmp->content = ft_strdup(value);
				if (!tmp->content)
					return (NULL);
				tmp->type = ARG;
			}
		}
		tmp = tmp->next;
	}
	return ((void *)1);
}
