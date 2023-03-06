/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 14:49:16 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// the echo builtin
int	ft_echo(t_exec	*exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	size_t		i;
	bool		endl;

	i = 1;
	endl = true;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		endl = false;
		i++;
	}
	while (args[i])
	{
		if (ft_putstr_fd((char *)args[i], STDOUT))
			return (ft_msg(exec, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
		if (args[i + 1] && args[i][0] != '\0' && ft_putchar_fd(' ', STDOUT))
			return (ft_msg(exec, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
		i++;
	}
	if (endl)
	{
		if (ft_putchar_fd('\n', STDOUT))
			return (ft_msg(exec, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
