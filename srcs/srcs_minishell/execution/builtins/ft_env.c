/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:20:32 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// print the env variables
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
