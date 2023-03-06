/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 14:16:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// the echo builtin
int	ft_echo(t_exec	*exec)
{
	char	**args;
	size_t	i;
	bool	endl;

	args = exec->args[exec->i];
	i = 0;
	endl = true;
	while (args[++i] && ft_strcmp(args[i], "-n") == 0)
		endl = false;
	while (args[++i])
	{
		if (ft_putstr_fd(args[i], STDOUT))
			return (ft_msg(exec, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
		if (args[i + 1] && args[i][0] != '\0')
		{
			if (ft_putchar_fd(' ', STDOUT))
				return (ft_msg(exec, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
		}
	}
	if (endl)
	{
		if (ft_putchar_fd('\n', STDOUT))
			return (ft_msg(exec, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
