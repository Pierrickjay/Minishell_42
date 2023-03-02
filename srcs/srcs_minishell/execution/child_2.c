/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:56:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 12:33:51 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_exec_pipe_infile_child(t_exec *exec)
{
	int		fd_in;

	fd_in = -1;
	if (exec->nb_redir_type[INFILE] || exec->nb_redir_type[HEREDOC])
	{
		fd_in = ft_open_infiles(exec->redir, exec->nb_redir_type[HEREDOC]);
		if (fd_in == FAILURE)
			return (ft_close_pipes(exec->pipes, (exec->nb - 1)), \
					ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_in, STDIN) == FAILURE)
			return (ft_close_pipes(exec->pipes, (exec->nb - 1)), close(fd_in), \
					ft_free_exec(exec), exit(EXIT_FAILURE));
		close(fd_in);
	}
	if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
		return (ft_close_pipes(exec->pipes, (exec->nb - 1)), close(fd_in), \
				ft_free_exec(exec), exit(EXIT_FAILURE));
}

static void	ft_exec_pipe_outfile_child(t_exec *exec)
{
	int		fd_out;

	fd_out = -1;
	if (dup2(exec->pipes[exec->i - 1][0], STDIN) == FAILURE)
		return (ft_close_pipes(exec->pipes, (exec->nb - 1)), \
				ft_free_exec(exec), exit(EXIT_FAILURE));
	if (exec->nb_redir_type[TRUNC] || exec->nb_redir_type[APPEND])
	{
		fd_out = ft_open_outfiles(exec->redir);
		if (fd_out == FAILURE)
			return (ft_close_pipes(exec->pipes, (exec->nb - 1)), \
					ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (ft_close_pipes(exec->pipes, (exec->nb - 1)), close(fd_out), \
					ft_free_exec(exec), exit(EXIT_FAILURE));
		close(fd_out);
	}
}

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
		if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
	}
	ft_close_pipes(exec->pipes, (exec->nb - 1));
	ft_exec_child(exec);
}
