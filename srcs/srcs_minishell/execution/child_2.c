/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:31:12 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 18:50:50 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_exec_pipe_infile_child(t_exec *exec)
{
	const int	n = exec->id_child;
	int			fd_in;

	fd_in = -1;
	fd_in = ft_open_infiles(exec, exec->redir[n]);
	if (dup2(fd_in, STDIN) == FAILURE)
		return (close(fd_in), ft_msg(exec, NULL, errno, &exit));
	ft_close(&fd_in);
	if (n < exec->nb_cmd - 1)
	{
		if (dup2(exec->pipes[n][1], STDOUT) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
	}
	ft_close(&exec->pipes[n][1]);
}

// the child process : outfile and pipe
static void	ft_exec_pipe_outfile_child(t_exec *exec)
{
	const int	n = exec->id_child;
	int			fd_out;

	fd_out = -1;
	if (n > 0)
	{
		if (dup2(exec->pipes[n - 1][0], STDIN) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[n - 1][0]);
	}
	fd_out = ft_open_outfiles(exec, exec->redir[n]);
	if (dup2(fd_out, STDOUT) == FAILURE)
		return (close(fd_out), ft_msg(exec, NULL, errno, &exit));
	ft_close(&fd_out);
}

static void	ft_exec_pipe_infile_outfile_child(t_exec *exec)
{
	const int	n = exec->id_child;
	int			fd_in;
	int			fd_out;

	fd_in = ft_open_infiles(exec, exec->redir[n]);
	if (dup2(fd_in, STDIN) == FAILURE)
		return (close(fd_in), ft_free_exec(exec), exit(EXIT_FAILURE));
	ft_close(&fd_in);
	fd_out = ft_open_outfiles(exec, exec->redir[n]);
	if (dup2(fd_out, STDOUT) == FAILURE)
		return (close(fd_out), ft_free_exec(exec), exit(EXIT_FAILURE));
	ft_close(&fd_out);
}

static void	ft_exec_pipe_dup(t_exec *exec)
{
	const int	n = exec->id_child;

	if (n == 0)
	{
		if (dup2(exec->pipes[n][1], STDOUT) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[n][0]);
	}
	else if (n == exec->nb_cmd - 1)
	{
		if (dup2(exec->pipes[n - 1][0], STDIN) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[n - 1][1]);
	}
	else
	{
		if (dup2(exec->pipes[n - 1][0], STDIN) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[n - 1][1]);
		if (dup2(exec->pipes[n][1], STDOUT) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[n][0]);
	}
}

// the child process : pipe and redirections
void	ft_exec_pipe_file_child(t_exec *exec)
{
	const int	n = exec->id_child;

	if (exec->infile[n] && exec->outfile[n])
		ft_exec_pipe_infile_outfile_child(exec);
	else if (exec->infile[n] && !exec->outfile[n])
		ft_exec_pipe_infile_child(exec);
	else if (!exec->infile[n] && exec->outfile[n])
		ft_exec_pipe_outfile_child(exec);
	else
		ft_exec_pipe_dup(exec);
	ft_close_pipes(exec->pipes, (exec->nb_cmd - 1));
	ft_exec_child(exec);
}
