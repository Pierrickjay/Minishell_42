/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:15:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/02 13:23:30 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exec_child(t_exec *exec)
{
	const int	n = exec->i;

	if (ft_is_builtins(exec) != FAILURE)
		return (ft_msg(exec, NULL, 0, &exit));
	if (ft_strncmp("./", exec->args[n][0], 2) == 0 && \
		access(exec->args[n][0], X_OK) != FAILURE)
	{
		execve(exec->args[n][0], exec->args[n], exec->env);
		return (ft_msg(exec, NULL, errno, &exit));
	}
	ft_exec_child_bis(exec, n);
}

void	ft_exec_child_bis(t_exec *exec, const int n)
{
	char	*tmp;
	char	*cmd;
	char	**path;

	path = ft_get_path(exec);
	tmp = ft_strjoin("/", exec->args[n][0]);
	if (!tmp)
		return (ft_free_strs(path), ft_msg(exec, NULL, MA, &exit));
	cmd = ft_access(tmp, path);
	if (!cmd)
		return (ft_free_strs(path), free(tmp), ft_msg(exec, NULL, MA, &exit));
	if (cmd == FAIL && ft_strcmp("exit", exec->args[n][0]) == 0)
		return (ft_free_strs(path), free(tmp), \
				ft_msg(exec, exec->args[n][0], EX, &exit));
	if (cmd == FAIL)
		return (ft_free_strs(path), free(tmp), \
				ft_msg(exec, exec->args[n][0], CM, &exit));
	free(tmp);
	execve(cmd, exec->args[n], exec->env);
	ft_free_child(exec, path, cmd);
	exit(EXIT_FAILURE);
}

void	ft_exec_pipe_child(t_exec *exec)
{
	if (exec->i == 0)
	{
		if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[exec->i][0]);
	}
	else if (exec->i == exec->nb - 1)
	{
		if (dup2(exec->pipes[exec->i - 1][0], STDIN) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[exec->i - 1][1]);
	}
	else
	{
		if (dup2(exec->pipes[exec->i - 1][0], STDIN) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[exec->i - 1][1]);
		if (dup2(exec->pipes[exec->i][1], STDOUT) == FAILURE)
			return (ft_msg(exec, NULL, errno, &exit));
		ft_close(&exec->pipes[exec->i][0]);
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
	ft_exec_redir_child_bis(exec, fd_in, fd_out);
	ft_exec_child(exec);
}

void	ft_exec_redir_child_bis(t_exec *exec, int fd_in, int fd_out)
{
	if (exec->nb_redir_type[INFILE] || exec->nb_redir_type[HEREDOC])
	{
		fd_in = ft_open_infiles(exec->redir, exec->nb_redir_type[HEREDOC]);
		if (fd_in == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_in, STDIN) == FAILURE)
			return (close(fd_in), ft_free_exec(exec), exit(EXIT_FAILURE));
		ft_close(&fd_in);
	}
	if (exec->nb_redir_type[TRUNC] || exec->nb_redir_type[APPEND])
	{
		fd_out = ft_open_outfiles(exec->redir);
		if (fd_out == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (close(fd_out), ft_free_exec(exec), exit(EXIT_FAILURE));
		ft_close(&fd_out);
	}
}
