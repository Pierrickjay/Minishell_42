/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:09:23 by pjay              #+#    #+#             */
/*   Updated: 2023/03/09 10:09:27 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// execution for no command and with redirection
int	ft_exec_parent_no_cmd(t_exec *exec)
{
	pid_t	*pid;

	pid = malloc(sizeof(*pid));
	exec->pid = pid;
	*pid = fork();
	if (*pid == -1)
		return (FAILURE);
	if (*pid == 0)
	{
		create_siga(CHILD);
		ft_exec_child_no_cmd(exec);
	}
	waitpid(*pid, &exec->status, WUNTRACED);
	printf("%d\n", *pid);
	deal_w_return_pid(exec->status);
	return (SUCCESS);
}

// child for one command and no redirection
int	ft_exec_parent(t_exec *exec)
{
	if (ft_builtins(exec) == FAILURE)
	{
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
	return (SUCCESS);
}

// child for n commands and no redirection
int	ft_exec_pipe_parent(t_exec *exec)
{
	int	i;

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
	return (SUCCESS);
}

// child for one command and redirection
int	ft_exec_redir_parent(t_exec *exec)
{
	ft_nb_redir_type(exec->redir, exec);
	if (ft_builtins(exec) == FAILURE)
	{
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

// child for n commands and redirection
int	ft_exec_pipe_redir_parent(t_exec *exec)
{
	int	i;

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
	return (SUCCESS);
}
