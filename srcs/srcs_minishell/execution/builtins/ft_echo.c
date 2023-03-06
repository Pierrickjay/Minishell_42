/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 16:13:48 by obouhlel         ###   ########.fr       */
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
	i = 1;
	endl = true;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		endl = false;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT);
		if (args[i + 1] && args[i][0] != '\0')
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (endl)
		ft_putchar_fd('\n', STDOUT);
	return (EXIT_SUCCESS);
}
