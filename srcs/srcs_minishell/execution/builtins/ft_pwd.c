/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:44 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/27 10:11:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_pwd(t_exec *exec)
{
	char	*pwd;

	pwd = ft_getenvi("PWD", exec->envi);
	if (!pwd)
		return (EXIT_FAILURE);
	ft_putendl_fd(pwd, STDOUT);
	return (EXIT_SUCCESS);
}
