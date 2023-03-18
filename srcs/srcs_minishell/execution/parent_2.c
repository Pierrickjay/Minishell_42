/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:31:57 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 18:50:23 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// execution for no command and with redirection
int	ft_exec_parent_no_cmd(t_exec *exec)
{
	pid_t	*pid;

	pid = malloc(sizeof(*pid));
	if (pid == NULL)
		return (FAILURE);
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
	if (exec->status == 2)
		exec->status = 130;
	deal_w_return_pid(exec->status);
	return (SUCCESS);
}

// child for n commands and no redirection
int	ft_exec_pipe_parent(t_exec *exec)
{
	int	i;

	while (exec->id_child < exec->nb_cmd)
	{
		if (ft_builtins(exec) == FAILURE)
		{
			exec->pid[exec->id_child] = fork();
			if (exec->pid[exec->id_child] == -1)
				return (FAILURE);
			if (exec->pid[exec->id_child] == 0)
			{
				create_siga(CHILD);
				ft_exec_pipe_child(exec);
			}
		}
		exec->id_child++;
	}
	ft_close_pipes(exec->pipes, (exec->nb_cmd - 1));
	i = 0;
	while (i < exec->nb_cmd)
		waitpid(exec->pid[i++], &exec->status, 0);
	return (SUCCESS);
}

// child for one command and redirection
int	ft_exec_redir_parent(t_exec *exec)
{
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

	while (exec->id_child < exec->nb_cmd)
	{
		if (ft_builtins(exec) == FAILURE)
		{
			exec->pid[exec->id_child] = fork();
			if (exec->pid[exec->id_child] == -1)
				return (FAILURE);
			if (exec->pid[exec->id_child] == 0)
			{
				create_siga(CHILD);
				ft_exec_pipe_file_child(exec);
			}
		}
		exec->id_child++;
	}
	ft_close_pipes(exec->pipes, (exec->nb_cmd - 1));
	i = 0;
	while (i < exec->nb_cmd)
		waitpid(exec->pid[i++], &exec->status, 0);
	return (SUCCESS);
}
