/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:53:12 by pjay              #+#    #+#             */
/*   Updated: 2023/03/09 13:30:00 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = count_split(split);
	while (i--)
		free(split[i]);
	free(split);
}

void	*free_inverse_split(char **split, int i, bool print)
{
	int	a;

	a = 0;
	if (print == TRUE)
		ft_putendl_fd("synthaxe error", 2);
	while (a < i)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

void	*free_str_quote_error(char *str)
{
	printf("here");
	ft_putendl_fd("synthaxe error", 2);
	free(str);
	return (NULL);
}
