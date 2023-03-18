/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:35:05 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:30:15 by obouhlel         ###   ########.fr       */
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
static void	ft_free_shell_bis(t_shell *shell)
{
	if (shell->redir)
	{
		ft_free_redir(shell->redir, shell->nb_cmd + shell->no_cmd + 1);
		shell->redir = NULL;
	}
	if (shell->pid)
		ft_free((void **)&shell->pid);
	if (shell->pipes)
	{
		ft_free_pipes(shell->pipes, (shell->nb_cmd - 1));
		shell->pipes = NULL;
	}
	if (shell->args)
	{
		ft_free_args(shell->args, shell->nb_cmd);
		shell->args = NULL;
	}
}

// free the exec struct and initialize it to NULL
void	ft_free_shell(t_shell *shell)
{
	if (shell->lst)
	{
		ft_free_lst(shell->lst);
		shell->lst = NULL;
	}
	if (shell->env)
	{
		ft_free_strs(shell->env);
		shell->env = NULL;
	}
	if (shell->envi)
	{
		ft_free_envi(shell->envi);
		shell->envi = NULL;
	}
	if (shell->infile)
		ft_free((void **)&shell->infile);
	if (shell->outfile)
		ft_free((void **)&shell->outfile);
	ft_free_shell_bis(shell);
	ft_free((void **)&shell);
}
