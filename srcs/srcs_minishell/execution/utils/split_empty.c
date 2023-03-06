/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:39:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 14:42:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_split_empty(char **strs)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (strs[i])
	{
		if (ft_strcmp(strs[i], "\0") == 0)
			n++;
		i++;
	}
	if (i == n)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
