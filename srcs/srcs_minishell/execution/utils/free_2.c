/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:35:05 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/22 12:05:15 by obouhlel         ###   ########.fr       */
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

void	ft_free_vars(t_vars *vars)
{
	if (vars->lst)
	{
		ft_free_lst(vars->lst);
		vars->lst = NULL;
	}
	if (vars->redir)
	{
		ft_free_redir(vars->redir);
		vars->redir = NULL;
	}
	if (vars->pid)
		ft_free((void **)&vars->pid);
	if (vars->pipes)
	{
		ft_free_pipes(vars->pipes, (vars->nb - 1));
		vars->pipes = NULL;
	}
	if (vars->args)
	{
		ft_free_args(vars->args, vars->nb);
		vars->args = NULL;
	}
	ft_free((void **)&vars);
}
