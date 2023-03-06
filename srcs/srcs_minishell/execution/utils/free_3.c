/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 13:39:46 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// free the child process variables
void	ft_free_child(t_exec *exec, char **path, char *cmd)
{
	if (exec)
		ft_free_exec(exec);
	if (path)
		ft_free_strs(path);
	if (cmd)
		free(cmd);
}

// free one element of the list of envi and initialize it to NULL
void	ft_free_envi_delone(t_envi *envi)
{
	ft_free((void **)&envi->key);
	ft_free((void **)&envi->value);
	ft_free((void **)&envi);
}
