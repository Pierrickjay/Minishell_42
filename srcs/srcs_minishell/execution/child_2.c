/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:56:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 15:55:31 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// the child process : infile, here doc, and pipe
static void	ft_exec_pipe_infile_child(t_exec *exec)
{
	int		fd_in;

	fd_in = -1;
	if (exec->nb_redir_type[INFILE] || exec->nb_redir_type[HEREDOC])
	{
		fd_in = ft_open_infiles(exec->redir, exec->nb_redir_type[HEREDOC], \
								exec->count_line, exec);
		if (fd_in == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		if (dup2(fd_in, STDIN) == FAILURE)
			return (close(fd_in), ft_msg(exec, NULL, errno, &exit));
		ft_close(&fd_in);
	}
	if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
		return (ft_msg(exec, NULL, errno, &exit));
	ft_close(&exec->pipes[exec->i][1]);
}

// the child process : outfile and pipe
static void	ft_exec_pipe_outfile_child(t_exec *exec)
{
	int		fd_out;

	fd_out = -1;
	if (dup2(exec->pipes[exec->i - 1][0], STDIN) == FAILURE)
		return (ft_msg(exec, NULL, errno, &exit));
	ft_close(&exec->pipes[exec->i - 1][0]);
	if (exec->nb_redir_type[TRUNC] || exec->nb_redir_type[APPEND])
	{
		fd_out = ft_open_outfiles(exec->redir, exec->count_line, exec);
		if (fd_out == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (close(fd_out), ft_msg(exec, NULL, errno, &exit));
		ft_close(&fd_out);
	}
}

// the child process : pipe and redirections
void	ft_exec_pipe_file_child(t_exec *exec)
{
	if (exec->i == 0)
		ft_exec_pipe_infile_child(exec);
	else if (exec->i == exec->nb - 1)
		ft_exec_pipe_outfile_child(exec);
	else
	{
		if (dup2(exec->pipes[exec->i - 1][0], STDIN) == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		ft_close(&exec->pipes[exec->i - 1][0]);
		if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		ft_close(&exec->pipes[exec->i][1]);
	}
	ft_close_pipes(exec->pipes, (exec->nb - 1));
	ft_exec_child(exec);
}

void	ft_exec_child_no_cmd(t_exec *exec)
{
	int	fd_in;
	int	fd_out;

	fd_in = ft_open_infiles(exec->redir, exec->nb_redir_type[HEREDOC], \
							exec->count_line, exec);
	if (fd_in == FAILURE)
		return (ft_msg(exec, NULL, errno, &exit));
	ft_close(&fd_in);
	fd_out = ft_open_outfiles(exec->redir, exec->count_line, exec);
	if (fd_out == FAILURE)
		return (ft_msg(exec, NULL, errno, &exit));
	ft_close(&fd_out);
	ft_free_exec(exec);
	exit(EXIT_SUCCESS);
}
