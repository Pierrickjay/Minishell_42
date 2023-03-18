/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:31:12 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 20:22:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_shell_pipe_infile_child(t_shell *shell)
{
	const int	n = shell->id_child;
	int			fd_in;

	fd_in = -1;
	fd_in = ft_open_infiles(shell, shell->redir[n]);
	if (dup2(fd_in, STDIN) == FAILURE)
		return (close(fd_in), ft_msg(shell, NULL, errno, &exit));
	ft_close(&fd_in);
	if (n < shell->nb_cmd - 1)
	{
		if (dup2(shell->pipes[n][1], STDOUT) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[n][1]);
	}
}

// the child process : outfile and pipe
static void	ft_shell_pipe_outfile_child(t_shell *shell)
{
	const int	n = shell->id_child;
	int			fd_out;

	fd_out = -1;
	if (n > 0)
	{
		if (dup2(shell->pipes[n - 1][0], STDIN) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[n - 1][0]);
	}
	fd_out = ft_open_outfiles(shell, shell->redir[n]);
	if (dup2(fd_out, STDOUT) == FAILURE)
		return (close(fd_out), ft_msg(shell, NULL, errno, &exit));
	ft_close(&fd_out);
}

static void	ft_shell_pipe_infile_outfile_child(t_shell *shell)
{
	const int	n = shell->id_child;
	int			fd_in;
	int			fd_out;

	fd_in = ft_open_infiles(shell, shell->redir[n]);
	if (dup2(fd_in, STDIN) == FAILURE)
		return (close(fd_in), ft_free_shell(shell), exit(EXIT_FAILURE));
	ft_close(&fd_in);
	fd_out = ft_open_outfiles(shell, shell->redir[n]);
	if (dup2(fd_out, STDOUT) == FAILURE)
		return (close(fd_out), ft_free_shell(shell), exit(EXIT_FAILURE));
	ft_close(&fd_out);
}

static void	ft_shell_pipe_dup(t_shell *shell)
{
	const int	n = shell->id_child;

	if (n == 0)
	{
		if (dup2(shell->pipes[n][1], STDOUT) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[n][0]);
	}
	else if (n == shell->nb_cmd - 1)
	{
		if (dup2(shell->pipes[n - 1][0], STDIN) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[n - 1][1]);
	}
	else
	{
		if (dup2(shell->pipes[n - 1][0], STDIN) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[n - 1][1]);
		if (dup2(shell->pipes[n][1], STDOUT) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[n][0]);
	}
}

// the child process : pipe and redirections
void	ft_shell_pipe_file_child(t_shell *shell)
{
	const int	n = shell->id_child;

	if (shell->infile[n] && shell->outfile[n])
		ft_shell_pipe_infile_outfile_child(shell);
	else if (shell->infile[n] && !shell->outfile[n])
		ft_shell_pipe_infile_child(shell);
	else if (!shell->infile[n] && shell->outfile[n])
		ft_shell_pipe_outfile_child(shell);
	else
		ft_shell_pipe_dup(shell);
	ft_close_pipes(shell->pipes, (shell->nb_cmd - 1));
	ft_shell_child(shell);
}
