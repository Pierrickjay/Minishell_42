/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:15:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 12:24:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exec_child(t_exec *exec)
{
	char	*cmd;
	char	*tmp;
	char	**path;

	if (access(exec->args[exec->i][0], X_OK) != FAILURE)
	{
		execve(exec->args[exec->i][0], exec->args[exec->i], exec->env);
		ft_free_exec(exec);
		exit(EXIT_FAILURE);
	}
	path = ft_get_path();
	if (!path)
		return (ft_free_exec(exec), exit(FAILURE));
	tmp = ft_strjoin("/", exec->args[exec->i][0]);
	if (!tmp)
		return (ft_free_child(exec, path, NULL), exit(FAILURE));
	cmd = ft_access(tmp, path);
	if (!cmd)
		return (ft_free_child(exec, path, cmd), exit(-1));
	free(tmp);
	execve(cmd, exec->args[exec->i], exec->env);
	ft_free_child(exec, path, cmd);
	exit(EXIT_FAILURE);
}

void	ft_exec_pipe_child(t_exec *exec)
{
	if (exec->i == 0)
	{
		if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
			return (ft_free_exec(exec), exit(FAILURE));
	}
	else if (exec->i == exec->nb - 1)
	{
		if (dup2(exec->pipes[exec->i - 1][0], STDIN) == FAILURE)
			return (ft_free_exec(exec), exit(FAILURE));
	}
	else
	{
		if (dup2(exec->pipes[exec->i - 1][0], STDIN) == FAILURE)
			return (ft_free_exec(exec), exit(FAILURE));
		if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
			return (ft_free_exec(exec), exit(FAILURE));
	}
	ft_close_pipes(exec->pipes, (exec->nb - 1));
	ft_exec_child(exec);
}

void	ft_exec_redir_child(t_exec *exec)
{
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	if (exec->nb_redir_type[REDIR_IN] || exec->nb_redir_type[REDIR_HEREDOC])
	{
		fd_in = ft_open_infiles(exec->redir, REDIR_IN, REDIR_HEREDOC, \
								exec->nb_redir_type[REDIR_HEREDOC]);
		if (fd_in == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_in, STDIN) == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		close(fd_in);
	}
	if (exec->nb_redir_type[REDIR_OUT] || exec->nb_redir_type[REDIR_APPEND])
	{
		fd_out = ft_open_outfiles(exec->redir, REDIR_OUT, REDIR_APPEND);
		if (fd_out == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		close(fd_out);
	}
	ft_exec_child(exec);
}
