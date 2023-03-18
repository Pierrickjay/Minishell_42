/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:44 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:31:03 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// print the current working directory
int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	(void)shell;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_msg(shell, NULL, errno, &exit), EXIT_FAILURE);
	ft_putendl_fd(pwd, STDOUT);
	free(pwd);
	return (EXIT_SUCCESS);
}
