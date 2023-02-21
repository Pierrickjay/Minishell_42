/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:46:55 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/19 23:06:18 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_builtins(t_vars *vars)
{
	if (!ft_strcmp(vars->args[vars->i][0], "echo"))
		return (ft_echo(vars));
	else if (!ft_strcmp(vars->args[vars->i][0], "cd"))
		return (ft_cd(vars));
	else if (!ft_strcmp(vars->args[vars->i][0], "env"))
		return (ft_env(vars));
	else if (!ft_strcmp(vars->args[vars->i][0], "exit"))
		return (ft_exit(vars));
	else if (!ft_strcmp(vars->args[vars->i][0], "export"))
		return (ft_export(vars));
	else if (!ft_strcmp(vars->args[vars->i][0], "unset"))
		return (ft_unset(vars));
	else if (!ft_strcmp(vars->args[vars->i][0], "pwd"))
		return (ft_pwd(vars));
	return (-1);
}
