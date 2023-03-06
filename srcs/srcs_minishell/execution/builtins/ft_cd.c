/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:07:08 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 15:19:33 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	ft_cd_bis(t_exec *exec)
{
	char	*pwd;

	pwd = ft_getenvi("HOME", exec->envi);
	if (!pwd)
		return (ft_msg_builtins("cd", NULL, HOME), 1);
	if (access(pwd, F_OK) == FAILURE)
		return (ft_msg_builtins("cd", pwd, PERM), 1);
	if (chdir(pwd) == FAILURE)
		return (ft_msg(NULL, pwd, errno, NULL), 1);
	if (exec->envi)
	{
		if (ft_cd_1(exec, pwd))
			return (ft_msg_malloc("ft_cd.c (111)"), 1);
	}
	return (EXIT_SUCCESS);
}

// return exit code and print error message and main of cd
int	ft_cd(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];

	if (!args[1] && ft_cd_bis(exec))
		return (EXIT_FAILURE);
	else
	{
		if (access(args[1], F_OK) == FAILURE)
			return (ft_msg_builtins("cd", (char *)args[1], PERM), 1);
		if (chdir(args[1]) == FAILURE)
			return (ft_msg_builtins("cd", (char *)args[1], PERM), 1);
		if (exec->envi)
		{
			if (ft_cd_1(exec, (char *)args[1]))
				return (ft_msg_malloc("ft_cd.c (120)"), 1);
		}
	}
	return (EXIT_SUCCESS);
}
