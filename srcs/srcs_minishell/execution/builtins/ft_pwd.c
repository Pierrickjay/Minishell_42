/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:44 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 13:29:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_pwd(t_exec *exec)
{
	char	*pwd;

	(void)exec;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("ERROR PWD", STDERR);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT);
	free(pwd);
	return (EXIT_SUCCESS);
}
