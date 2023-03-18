/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 15:37:19 by obouhlel         ###   ########.fr       */
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

// free the heredoc structure
void	ft_free_heredoc(t_heredoc *heredoc)
{
	if (heredoc->lst)
		ft_free_lst(heredoc->lst);
	if (heredoc->envi)
		ft_free_envi(heredoc->envi);
}
