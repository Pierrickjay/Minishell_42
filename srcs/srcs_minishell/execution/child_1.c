/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:15:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:16:29 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// no cmd but redirection
void	ft_shell_child_no_cmd(t_shell *shell)
{
	const int	n = shell->id_child;
	int			fd_in;
	int			fd_out;

	fd_in = -1;
	fd_out = -1;
	fd_in = ft_open_infiles(shell, shell->redir[n]);
	ft_close(&fd_in);
	fd_out = ft_open_outfiles(shell, shell->redir[n]);
	ft_close(&fd_out);
	ft_free_shell(shell);
	exit(EXIT_SUCCESS);
}

// the main execution child process
void	ft_shell_child(t_shell *shell)
{
	const int	n = shell->id_child;

	if (builtins_in_child(shell) != FAILURE)
		return (ft_msg(shell, NULL, 0, &exit));
	if ((ft_strncmp("./", shell->args[n][0], 2) == 0 && \
		access(shell->args[n][0], X_OK) != FAILURE) || \
		ft_strchr(shell->args[n][0], '/') != NULL)
	{
		execve(shell->args[n][0], shell->args[n], shell->env);
		ft_msg(shell, shell->args[n][0], errno, &exit);
	}
	ft_shell_child_bis(shell, n);
}

// the main execution child process bis
void	ft_shell_child_bis(t_shell *shell, const int n)
{
	char	*tmp;
	char	*cmd;
	char	**path;

	path = ft_get_path(shell);
	tmp = ft_strjoin("/", shell->args[n][0]);
	if (!tmp)
		return (ft_free_strs(path), ft_msg(shell, NULL, MA, &exit));
	cmd = ft_access(tmp, path);
	if (!cmd)
		return (ft_free_strs(path), free(tmp), ft_msg(shell, NULL, MA, &exit));
	if (cmd == FAIL && !ft_strcmp("exit", shell->args[n][0]))
		return (ft_free_strs(path), free(tmp), \
				ft_msg(shell, shell->args[n][0], EX, &exit));
	if (cmd == FAIL)
		return (ft_free_strs(path), free(tmp), \
				ft_msg(shell, shell->args[n][0], CM, &exit));
	free(tmp);
	execve(cmd, shell->args[n], shell->env);
	ft_free_child(shell, path, cmd);
	exit(EXIT_FAILURE);
}

// child process for pipes
void	ft_shell_pipe_child(t_shell *shell)
{
	if (shell->id_child == 0)
	{
		if (dup2(shell->pipes[shell->id_child][1], STDOUT) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[shell->id_child][0]);
	}
	else if (shell->id_child == shell->nb_cmd - 1)
	{
		if (dup2(shell->pipes[shell->id_child - 1][0], STDIN) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[shell->id_child - 1][1]);
	}
	else
	{
		if (dup2(shell->pipes[shell->id_child - 1][0], STDIN) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[shell->id_child - 1][1]);
		if (dup2(shell->pipes[shell->id_child][1], STDOUT) == FAILURE)
			return (ft_msg(shell, NULL, errno, &exit));
		ft_close(&shell->pipes[shell->id_child][0]);
	}
	ft_close_pipes(shell->pipes, (shell->nb_cmd - 1));
	ft_shell_child(shell);
}

// child process for redirections
void	ft_shell_redir_child(t_shell *shell)
{
	const int	n = shell->id_child;
	int			fd_in;
	int			fd_out;

	if (shell->infile[n])
	{
		fd_in = ft_open_infiles(shell, shell->redir[n]);
		if (dup2(fd_in, STDIN) == FAILURE)
			return (close(fd_in), ft_free_shell(shell), exit(EXIT_FAILURE));
		ft_close(&fd_in);
	}
	if (shell->outfile[n])
	{
		fd_out = ft_open_outfiles(shell, shell->redir[n]);
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (close(fd_out), ft_free_shell(shell), exit(EXIT_FAILURE));
		ft_close(&fd_out);
	}
	ft_shell_child(shell);
}
