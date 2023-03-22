/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/22 09:32:30 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	write_mines(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != -2)
	{
		if (write(STDOUT, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	check_mines(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -2)
			return (-1);
		i++;
	}
	return (0);
}

// check if the argument is -nnnnnnn or -n
static int	ft_echo_check_endl(char *str)
{
	size_t	i;
	size_t	len;

	if (str[0] == '\0')
		return (0);
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
// modif i = 1 i++ dans la premiere boucle et enlever le ++i en condition
int	ft_echo(t_shell	*shell)
{
	const char	**args = (const char **)shell->args[shell->id_child];
	size_t		i;
	bool		endl;

	i = 0;
	endl = true;
	while (args[++i] && ft_echo_check_endl((char *)args[i]))
		endl = false;
	while (args[i])
	{
		if (write_mines((char *)args[i]) == -1)
			return (ft_msg(shell, ECHO_ERROR, errno, &exit), EXIT_FAILURE);
		if (args[i + 1] && check_mines((char *)args[i]) != -1
			&& ft_putchar_fd(' ', STDOUT))
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
