/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:58:59 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/22 11:14:43 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
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
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	ft_free_pipes(int **pipes, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		free(pipes[i]);
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

void	ft_free_redir(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
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
		free(vars->pid);
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
	free(vars);
}
