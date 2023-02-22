/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:28:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/22 14:29:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_exec	*main_exec(t_list *lst, char **env)
{
	t_exec	*exec;
	int		status;

	status = 0;
	exec = ft_init_exec(lst, env);
	if (!exec)
		return (NULL);
	if (exec->nb == 0)
		return (ft_putendl_fd(SYNTAX, 2), exec);
	if (exec->nb == 1 && exec->nb_redir == 0)
		status = ft_exec_parent(exec);
	else if (exec->nb > 1 && exec->nb_redir == 0)
		status = ft_exec_pipe_parent(exec);
	else if (exec->nb == 1 && exec->nb_redir > 0)
		status = ft_exec_redir_parent(exec);
	else if (exec->nb > 1 && exec->nb_redir > 0)
		status = ft_exec_pipe_redir_parent(exec);
	if (status == FAILURE)
	{
		ft_putendl_fd("minishell: fork failed", STDERR);
		return (exec);
	}
	return (exec);
}

int	ft_exec_parent(t_exec *exec)
{
	exec->pid[0] = fork();
	if (exec->pid[0] == -1)
		return (FAILURE);
	if (exec->pid[0] == 0)
		ft_exec_child(exec);
	waitpid(exec->pid[0], &exec->status, 0);
	return (SUCCESS);
}

int	ft_exec_pipe_parent(t_exec *exec)
{
	size_t	i;

	while (exec->i < exec->nb)
	{
		exec->pid[exec->i] = fork();
		if (exec->pid[exec->i] == -1)
			return (FAILURE);
		if (exec->pid[exec->i] == 0)
			ft_exec_pipe_child(exec);
		exec->i++;
	}
	ft_close_pipes(exec->pipes, (exec->nb - 1));
	i = 0;
	while (i < exec->nb)
		waitpid(exec->pid[i++], &exec->status, 0);
	return (SUCCESS);
}

int	ft_exec_redir_parent(t_exec *exec)
{
	ft_nb_redir_type(exec->redir, exec);
	exec->pid[0] = fork();
	if (exec->pid[0] == -1)
		return (FAILURE);
	if (exec->pid[0] == 0)
		ft_exec_redir_child(exec);
	waitpid(exec->pid[0], &exec->status, 0);
	return (SUCCESS);
}

int	ft_exec_pipe_redir_parent(t_exec *exec)
{
	size_t	i;

	ft_nb_redir_type(exec->redir, exec);
	while (exec->i < exec->nb)
	{
		exec->pid[exec->i] = fork();
		if (exec->pid[exec->i] == -1)
			return (FAILURE);
		if (exec->pid[exec->i] == 0)
			ft_exec_pipe_file_child(exec);
		exec->i++;
	}
	ft_close_pipes(exec->pipes, (exec->nb - 1));
	i = 0;
	while (i < exec->nb)
		waitpid(exec->pid[i++], &exec->status, 0);
	return (SUCCESS);
}
