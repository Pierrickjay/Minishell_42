/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:26:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 16:36:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// msg for exit
static void	ft_msg_exit(char **args, const int n)
{
	if (n == 1)
		return ;
	else if (n >= 2 && ft_all_isdigit(args[1]))
	{
		ft_putstr_fd("exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else
		ft_putendl_fd("exit: too many arguments", STDERR);
}

// print the error message
static void	ft_msg_bis(char *str, int value, char **args)
{
	const int	n = ft_nb_args_child(args);

	if (value == MA)
		ft_msg_malloc(str);
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
		ft_msg_exit(args, n);
}

// print the error message and/or free and/or exit
void	ft_msg(t_exec *exec, char *str, int value, void (*f)(int))
{
	if (value > 0 && str)
		perror(str);
	else if (value > 0)
		ft_putendl_fd(strerror(errno), STDERR);
	else if (value < 0)
		ft_msg_bis(str, value, exec->args[exec->i]);
	if (!f && exec)
		ft_free_exec(exec);
	if (f)
	{
		if (exec)
		{
			if (exec->pipes)
				ft_close_pipes(exec->pipes, (exec->nb - 1));
			ft_free_exec(exec);
		}
		f(value);
	}
}

// print the error message for builtins
void	ft_msg_builtins(char *cmd, char *arg, char *str)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (arg && ft_strcmp(cmd, "cd") == 0)
	{
		ft_putstr_fd(arg, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	else if (arg && ft_strcmp(cmd, "export") == 0)
	{
		ft_putchar_fd('`', STDERR);
		ft_putstr_fd(arg, STDERR);
		ft_putstr_fd("': ", STDERR);
	}
	if (str)
		ft_putendl_fd(str, STDERR);
}

// message for malloc fail or not
void	ft_msg_malloc(char *files)
{
	if (files)
	{
		ft_putstr_fd(files, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd("malloc fail", STDERR);
}
