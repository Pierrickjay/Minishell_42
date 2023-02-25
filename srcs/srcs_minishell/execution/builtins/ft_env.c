/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 16:25:18 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_env(t_exec *exec)
{
	size_t	i;

	i = 0;
	while (exec->env[i])
	{
		ft_putendl_fd(exec->env[i], STDOUT);
		i++;
	}
	return (EXIT_SUCCESS);
}
