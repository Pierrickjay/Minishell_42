/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:26:23 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// check if the argument is -nnnnnnn or -n
static int	ft_echo_check_endl(char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (i == len)
		return (1);
	return (0);
}

// the echo builtin
int	ft_echo(t_shell	*shell)
{
	const char	**args = (const char **)shell->args[shell->id_child];
	size_t		i;
	bool		endl;

	i = 1;
	endl = true;
	while (args[i] && ft_echo_check_endl((char *)args[i]))
	{
		endl = false;
		i++;
	}
	while (args[i])
	{
		if (ft_putstr_fd((char *)args[i], STDOUT))
			return (ft_msg(shell, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
		if (args[i + 1] && args[i][0] != '\0' && ft_putchar_fd(' ', STDOUT))
			return (ft_msg(shell, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
		i++;
	}
	if (endl)
	{
		if (ft_putchar_fd('\n', STDOUT))
			return (ft_msg(shell, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
