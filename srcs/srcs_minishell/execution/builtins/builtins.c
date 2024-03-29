/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:46:55 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:16:43 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// builtins in child process
int	builtins_in_child(t_shell *shell)
{
	if (!ft_strcmp(shell->args[shell->id_child][0], "echo"))
		return (ft_echo(shell));
	else if (!ft_strcmp(shell->args[shell->id_child][0], "env"))
		return (ft_env(shell));
	else if (!ft_strcmp(shell->args[shell->id_child][0], "pwd"))
		return (ft_pwd(shell));
	else if (!ft_strcmp(shell->args[shell->id_child][0], "export"))
		return (ft_envi_print(shell, shell->envi), EXIT_SUCCESS);
	return (FAILURE);
}

// builtins in parent process
int	builtins_in_parent(t_shell *shell)
{
	if (!ft_strcmp(shell->args[shell->id_child][0], "cd"))
	{
		shell->status = ft_cd(shell);
		return (shell->status);
	}
	else if (!ft_strcmp(shell->args[shell->id_child][0], "export"))
	{
		shell->status = ft_export(shell);
		if (shell->status == FAILURE)
		{
			shell->status = 0;
			return (FAILURE);
		}
		return (shell->status);
	}
	else if (!ft_strcmp(shell->args[shell->id_child][0], "unset"))
	{
		shell->status = ft_unset(shell);
		return (shell->status);
	}
	return (FAILURE);
}
