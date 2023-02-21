/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:23:43 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/21 14:57:20 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_close_pipes(int **pipes, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
}
