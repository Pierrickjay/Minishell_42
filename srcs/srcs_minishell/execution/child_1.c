/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:15:28 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/20 13:08:55 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exec_child(t_vars *vars)
{
	char	*cmd;
	char	*tmp;
	char	**path;

	if (access(vars->args[vars->i][0], X_OK) != FAILURE)
	{
		execve(vars->args[vars->i][0], vars->args[vars->i], vars->env);
		ft_free_vars(vars);
		exit(EXIT_FAILURE);
	}
	path = ft_get_path();
	if (!path)
		return (ft_free_vars(vars), exit(FAILURE));
	tmp = ft_strjoin("/", vars->args[vars->i][0]);
	if (!tmp)
		return (ft_free_vars(vars), ft_free_strs(path), exit(FAILURE));
	cmd = ft_access(tmp, path);
	if (!cmd)
		return (ft_free_vars(vars), ft_free_strs(path), free(tmp), exit(-1));
	free(tmp);
	execve(cmd, vars->args[vars->i], vars->env);
	ft_free_vars(vars);
	ft_free_strs(path);
	free(cmd);
	exit(EXIT_FAILURE);
}

void	ft_exec_pipe_child(t_vars *vars)
{
	if (vars->i == 0)
	{
		if (dup2(vars->pipes[vars->i][1], STDOUT) == FAILURE)
			return (ft_free_vars(vars), exit(FAILURE));
	}
	else if (vars->i == vars->nb - 1)
	{
		if (dup2(vars->pipes[vars->i - 1][0], STDIN) == FAILURE)
			return (ft_free_vars(vars), exit(FAILURE));
	}
	else
	{
		if (dup2(vars->pipes[vars->i - 1][0], STDIN) == FAILURE)
			return (ft_free_vars(vars), exit(FAILURE));
		if (dup2(vars->pipes[vars->i][1], STDOUT) == FAILURE)
			return (ft_free_vars(vars), exit(FAILURE));
	}
	ft_close_pipes(vars->pipes, (vars->nb - 1));
	ft_exec_child(vars);
}

void	ft_exec_redir_child(t_vars *vars)
{
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
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
	if (vars->nb_redir_type[REDIR_OUT] || vars->nb_redir_type[REDIR_APPEND])
	{
		fd_out = ft_open_outfiles(vars->redir, REDIR_OUT, REDIR_APPEND);
		if (fd_out == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
		if (dup2(fd_out, STDOUT) == FAILURE)
			return (ft_free_vars(vars), exit(EXIT_FAILURE));
		close(fd_out);
	}
	ft_exec_child(vars);
}
