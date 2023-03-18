/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:08:58 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:28:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// print the env variables
int	ft_env(t_shell *shell)
{
	size_t		i;
	const int	id_child = shell->id_child;

	if (!shell->env)
		return (EXIT_SUCCESS);
	if (ft_nb_args_child(shell->args[id_child]) > 1)
		return (ft_msg_builtins("env", shell->args[id_child][1], TOOMANY), 127);
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], STDOUT);
		i++;
	}
	return (EXIT_SUCCESS);
}
