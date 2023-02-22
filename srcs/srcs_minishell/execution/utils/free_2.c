/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:35:05 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/22 14:29:07 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->lst)
	{
		ft_free_lst(exec->lst);
		exec->lst = NULL;
	}
	if (exec->redir)
	{
		ft_free_redir(exec->redir);
		exec->redir = NULL;
	}
	if (exec->pid)
		ft_free((void **)&exec->pid);
	if (exec->pipes)
	{
		ft_free_pipes(exec->pipes, (exec->nb - 1));
		exec->pipes = NULL;
	}
	if (exec->args)
	{
		ft_free_args(exec->args, exec->nb);
		exec->args = NULL;
	}
	ft_free((void **)&exec);
}
