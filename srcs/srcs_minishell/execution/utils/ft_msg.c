/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:26:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 12:44:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	ft_msg_bis(char *str, int value)
{
	if (value == -1)
		ft_putendl_fd("Malloc fail", STDERR);
	else if (value == -2)
		ft_putendl_fd("Syntaxe error", STDERR);
	else if (value == -3)
		ft_putendl_fd("PATH not set", STDERR);
	else if (value == -4)
	{
		if (str)
		{
			ft_putstr_fd(str, STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd("Command not found", STDERR);
	}
}

void	ft_msg(t_exec *exec, char *str, int value, void (*f)(int))
{
	if (value > 0 && str)
		perror(str);
	else if (value > 0)
		ft_putendl_fd(strerror(errno), STDERR);
	else if (value < 0)
	{
		ft_msg_bis(str, value);
	}
	if (!f && exec)
		ft_free_exec(exec);
	if (f)
	{
		if (exec)
		{
			ft_close_pipes(exec->pipes, (exec->nb - 1));
			ft_free_exec(exec);
		}
		f(value);
	}
}
