/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:07:08 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:29:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// return exit code and print error message and main of cd
int	ft_cd(t_shell *shell)
{
	const char	**args = (const char **)shell->args[shell->id_child];

	if (ft_nb_args_child(shell->args[shell->id_child]) > 2)
		return (ft_msg_builtins("cd", NULL, TOOMANY), 1);
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (ft_cd_home(shell))
			return (EXIT_FAILURE);
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		if (ft_cd_back(shell))
			return (EXIT_FAILURE);
	}
	else
	{
		if (ft_cd_go_to(shell, args[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
