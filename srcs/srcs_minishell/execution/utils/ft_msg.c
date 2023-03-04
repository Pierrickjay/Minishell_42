/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:26:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 16:37:19 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	ft_msg_bis_bis(char *str, int value)
{
	if (value == EXP1)
	{
		if (str)
		{
			ft_putstr_fd(str, STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd("not a valid identifier", STDERR);
	}
}

static void	ft_msg_bis(char *str, int value)
{
	if (value == MA)
		ft_putendl_fd("malloc fail", STDERR);
	else if (value == SY)
		ft_putendl_fd("syntaxe error", STDERR);
	else if (value == PA)
		ft_putendl_fd("PATH not set", STDERR);
	else if (value == CM)
	{
		if (str)
		{
			ft_putstr_fd(str, STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd("command not found", STDERR);
	}
	else if (value == EX)
	{
		if (str)
		{
			ft_putstr_fd(str, STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd("too many arguments", STDERR);
	}
	ft_msg_bis_bis(str, value);
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
