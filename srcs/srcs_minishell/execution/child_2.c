/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:56:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/20 13:08:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_exec_pipe_infile_child(t_vars *vars)
{
	int		fd_in;

	fd_in = -1;
	if (vars->nb_redir_type[REDIR_IN] || vars->nb_redir_type[REDIR_HEREDOC])
	{
		fd_in = ft_open_infiles(vars->redir, REDIR_IN, REDIR_HEREDOC, \
								vars->nb_redir_type[REDIR_HEREDOC]);
		if (fd_in == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
		if (dup2(fd_in, STDIN) == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
		close(fd_in);
	}
	if (dup2(vars->pipes[vars->i][1], STDOUT) == FAILURE)
		return (ft_free_vars(vars), exit(EXIT_FAILURE));
}

static void	ft_exec_pipe_outfile_child(t_vars *vars)
{
	int		fd_out;

	fd_out = -1;
	if (dup2(vars->pipes[vars->i - 1][0], STDIN) == FAILURE)
		return (ft_free_vars(vars), exit(EXIT_FAILURE));
	if (vars->nb_redir_type[REDIR_OUT] || vars->nb_redir_type[REDIR_APPEND])
	{
		fd_out = ft_open_outfiles(vars->redir, REDIR_OUT, REDIR_APPEND);
		if (fd_out == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
		close(fd_out);
	}
}

void	ft_exec_pipe_file_child(t_vars *vars)
{
	if (vars->i == 0)
		ft_exec_pipe_infile_child(vars);
	else if (vars->i == vars->nb - 1)
		ft_exec_pipe_outfile_child(vars);
	else
	{
		if (dup2(vars->pipes[vars->i - 1][0], STDIN) == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
		if (dup2(vars->pipes[vars->i][1], STDOUT) == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
	}
	ft_close_pipes(vars->pipes, (vars->nb - 1));
	ft_exec_child(vars);
}
