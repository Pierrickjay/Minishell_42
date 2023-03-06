/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:44 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 15:31:33 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// print the current working directory
int	ft_pwd(t_exec *exec)
{
	char	*pwd;

	(void)exec;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_msg(exec, NULL, errno, &exit), EXIT_FAILURE);
	ft_putendl_fd(pwd, STDOUT);
	free(pwd);
	return (EXIT_SUCCESS);
}
