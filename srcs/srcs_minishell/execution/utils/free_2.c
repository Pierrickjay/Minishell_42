/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:35:05 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 11:14:46 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// free a pointer and initialize it to NULL
void	ft_free(void **ptr)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// free a pointer of pointer n and initialize it to NULL
void	ft_free_strs_n(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_free((void **)&strs[i]);
		i++;
	}
	free(strs);
}

// free the list of envi and initialize it to NULL
void	ft_free_envi(t_envi *envi)
{
	t_envi	*tmp;

	while (envi)
	{
		tmp = envi->next;
		ft_free((void **)&envi->key);
		ft_free((void **)&envi->value);
		ft_free((void **)&envi);
		envi = tmp;
	}
}

// free the exec struct and initialize it to NULL
static void	ft_free_exec_bis(t_exec *exec)
{
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
}

// free the exec struct and initialize it to NULL
void	ft_free_exec(t_exec *exec)
{
	if (exec->lst)
	{
		ft_free_lst(exec->lst);
		exec->lst = NULL;
	}
	if (exec->env)
	{
		ft_free_strs(exec->env);
		exec->env = NULL;
	}
	if (exec->envi)
	{
		ft_free_envi(exec->envi);
		exec->envi = NULL;
	}
	// if (exec->redir)
	// {
	// 	ft_free_redir(exec->redir);
	// 	exec->redir = NULL;
	// }
	ft_free_exec_bis(exec);
	ft_free((void **)&exec);
}
