/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:46:55 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 16:20:55 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_is_builtins(t_exec *exec)
{
	if (!ft_strcmp(exec->args[exec->i][0], "echo"))
		return (ft_echo(exec));
	else if (!ft_strcmp(exec->args[exec->i][0], "env"))
		return (ft_env(exec));
	else if (!ft_strcmp(exec->args[exec->i][0], "pwd"))
		return (ft_pwd(exec));
	return (-1);
}

int	ft_builtins(t_exec *exec)
{
	if (!ft_strcmp(exec->args[exec->i][0], "cd"))
		return (ft_cd(exec));
	else if (!ft_strcmp(exec->args[exec->i][0], "export"))
		return (ft_export(exec));
	else if (!ft_strcmp(exec->args[exec->i][0], "unset"))
		return (ft_unset(exec));
	return (-1);
}
