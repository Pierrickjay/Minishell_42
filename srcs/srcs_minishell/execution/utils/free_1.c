/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:19:00 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 12:13:23 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		ft_free((void **)&strs[i]);
		i++;
	}
	free(strs);
}

void	ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_free((void **)&lst->content);
		ft_free((void **)&lst);
		lst = tmp;
	}
}

void	ft_free_pipes(int **pipes, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_free((void **)&pipes[i]);
		i++;
	}
	free(pipes);
}

void	ft_free_args(char ***args, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
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
		ft_free_lst(vars->redir);
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
