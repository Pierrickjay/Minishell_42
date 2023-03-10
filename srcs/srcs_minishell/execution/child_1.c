/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:15:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 17:12:01 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// the main execution child process
void	ft_exec_child(t_exec *exec)
{
	const int	n = exec->i;

	if (ft_is_builtins(exec) != FAILURE)
		return (ft_msg(exec, NULL, 0, &exit));
	if ((ft_strncmp("./", exec->args[n][0], 2) == 0 && \
		access(exec->args[n][0], X_OK) != FAILURE) || \
		ft_strchr(exec->args[n][0], '/') != NULL)
	{
		execve(exec->args[n][0], exec->args[n], exec->env);
		ft_msg(exec, exec->args[n][0], errno, &exit);
	}
	ft_exec_child_bis(exec, n);
}

// the main execution child process bis
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
	if (cmd == FAIL && !ft_strcmp("exit", exec->args[n][0]))
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

// child process for pipes
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

// child process for redirections
void	ft_exec_redir_child(t_exec *exec)
{
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	ft_exec_redir_child_bis(exec, fd_in, fd_out);
	ft_exec_child(exec);
}

// child process for redirections bis
void	ft_exec_redir_child_bis(t_exec *exec, int fd_in, int fd_out)
{
	const int	n = exec->i;

	if (exec->infile[n])
	{
		fd_in = ft_open_infiles(exec->redir[n], \
				exec->nb_redir_type[n][HEREDOC], exec->count_line, exec);
		if (fd_in == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_in, STDIN) == FAILURE)
			return (close(fd_in), ft_free_exec(exec), exit(EXIT_FAILURE));
		ft_close(&fd_in);
	}
	if (exec->outfile[n])
	{
		fd_out = ft_open_outfiles(exec->redir[n], exec->count_line, exec);
		if (fd_out == FAILURE)
			return (ft_free_exec(exec), exit(EXIT_FAILURE));
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (close(fd_out), ft_free_exec(exec), exit(EXIT_FAILURE));
		ft_close(&fd_out);
	}
}
