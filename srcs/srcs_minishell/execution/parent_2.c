/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:36:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 22:38:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern sig_atomic_t	g_check;

void	deal_w_return_pid(int status)
{
	if (status == 2)
		ft_putchar_fd('\n', STDERR);
	else if (status == 131)
		ft_putendl_fd("Quit (core dumped)\n", STDERR);
	else
		return ;
}

int	ft_exec_parent(t_exec *exec)
{
	g_check = 1;
	if (ft_builtins(exec) == FAILURE)
	{
		g_check++;
		exec->pid[0] = fork();
		if (exec->pid[0] == -1)
			return (FAILURE);
		if (exec->pid[0] == 0)
		{
			create_siga(CHILD);
			ft_exec_child(exec);
		}
	}
	waitpid(exec->pid[0], &exec->status, WUNTRACED);
	deal_w_return_pid(exec->status);
	g_check = 0;
	return (SUCCESS);
}

int	ft_exec_pipe_parent(t_exec *exec)
{
	int	i;

	g_check = 1;
	while (exec->i < exec->nb)
	{
		if (ft_builtins(exec) == FAILURE)
		{
			exec->pid[exec->i] = fork();
			if (exec->pid[exec->i] == -1)
				return (FAILURE);
			if (exec->pid[exec->i] == 0)
			{
				create_siga(CHILD);
				ft_exec_pipe_child(exec);
			}
		}
		exec->i++;
	}
	ft_close_pipes(exec->pipes, (exec->nb - 1));
	i = 0;
	while (i < exec->nb)
		waitpid(exec->pid[i++], &exec->status, 0);
	g_check = 0;
	return (SUCCESS);
}

int	ft_exec_redir_parent(t_exec *exec)
{
	ft_nb_redir_type(exec->redir, exec);
	if (ft_builtins(exec) == FAILURE)
	{
		g_check++;
		exec->pid[0] = fork();
		if (exec->pid[0] == -1)
			return (FAILURE);
		if (exec->pid[0] == 0)
		{
			create_siga(CHILD);
			ft_exec_redir_child(exec);
		}
	}
	waitpid(exec->pid[0], &exec->status, 0);
	return (SUCCESS);
}

int	ft_exec_pipe_redir_parent(t_exec *exec)
{
	int	i;

	g_check = 1;
	ft_nb_redir_type(exec->redir, exec);
	while (exec->i < exec->nb)
	{
		if (ft_builtins(exec) == FAILURE)
		{
			exec->pid[exec->i] = fork();
			if (exec->pid[exec->i] == -1)
				return (FAILURE);
			if (exec->pid[exec->i] == 0)
			{
				create_siga(CHILD);
				ft_exec_pipe_file_child(exec);
			}
		}
		exec->i++;
	}
	ft_close_pipes(exec->pipes, (exec->nb - 1));
	i = 0;
	while (i < exec->nb)
		waitpid(exec->pid[i++], &exec->status, 0);
	g_check = 0;
	return (SUCCESS);
}
