/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:46:55 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 18:17:16 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// builtins in child process
int	ft_is_builtins(t_exec *exec)
{
	if (!ft_strcmp(exec->args[exec->i][0], "echo"))
		return (ft_echo(exec));
	else if (!ft_strcmp(exec->args[exec->i][0], "env"))
		return (ft_env(exec));
	else if (!ft_strcmp(exec->args[exec->i][0], "pwd"))
		return (ft_pwd(exec));
	else if (!ft_strcmp(exec->args[exec->i][0], "export"))
		return (ft_envi_print(exec, exec->envi), EXIT_SUCCESS);
	return (FAILURE);
}

// builtins in parent process
int	ft_builtins(t_exec *exec)
{
	if (!ft_strcmp(exec->args[exec->i][0], "cd"))
	{
		exec->status = ft_cd(exec);
		return (exec->status);
	}
	else if (!ft_strcmp(exec->args[exec->i][0], "export"))
	{
		exec->status = ft_export(exec);
		if (exec->status == FAILURE)
		{
			exec->status = 0;
			return (FAILURE);
		}
		return (exec->status);
	}
	else if (!ft_strcmp(exec->args[exec->i][0], "unset"))
	{
		exec->status = ft_unset(exec);
		return (exec->status);
	}
	return (FAILURE);
}
