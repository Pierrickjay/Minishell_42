/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 13:49:44 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_free_child(t_exec *exec, char **path, char *cmd)
{
	if (exec)
		ft_free_exec(exec);
	if (path)
		ft_free_strs(path);
	if (cmd)
		free(cmd);
}
