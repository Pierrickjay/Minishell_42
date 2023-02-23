/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:28:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 10:38:05 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern sig_atomic_t	g_check;

t_vars	*main_exec(t_list *lst, char **env)
{
	t_vars	*vars;
	int		status;

	status = 0;
	vars = ft_init_vars(lst, env);
	if (!vars)
		return (NULL);
	if (vars->nb == 0)
		return (ft_putendl_fd(SYNTAX, 2), vars);
	if (vars->nb == 1 && vars->nb_redir == 0)
		status = ft_exec_parent(vars);
	else if (vars->nb > 1 && vars->nb_redir == 0)
		status = ft_exec_pipe_parent(vars);
	else if (vars->nb == 1 && vars->nb_redir > 0)
		status = ft_exec_redir_parent(vars);
	else if (vars->nb > 1 && vars->nb_redir > 0)
		status = ft_exec_pipe_redir_parent(vars);
	if (status == FAILURE)
	{
		ft_putendl_fd("minishell: fork failed", STDERR);
		return (vars);
	}
	return (vars);
}

int	ft_exec_parent(t_vars *vars)
{
	g_check = 1;
	vars->pid[0] = fork();
	if (vars->pid[0] == -1)
		return (FAILURE);
	if (vars->pid[0] == 0)
		ft_exec_child(vars);
	waitpid(vars->pid[0], &vars->status, 0);
	g_check = 0;
	return (SUCCESS);
}

int	ft_exec_pipe_parent(t_vars *vars)
{
	size_t	i;

	g_check = 1;
	while (vars->i < vars->nb)
	{
		vars->pid[vars->i] = fork();
		if (vars->pid[vars->i] == -1)
			return (FAILURE);
		if (vars->pid[vars->i] == 0)
			ft_exec_pipe_child(vars);
		vars->i++;
	}
	ft_close_pipes(vars->pipes, (vars->nb - 1));
	i = 0;
	while (i < vars->nb)
		waitpid(vars->pid[i++], &vars->status, 0);
	g_check = 0;
	return (SUCCESS);
}

int	ft_exec_redir_parent(t_vars *vars)
{
	g_check = 1;
	ft_nb_redir_type(vars->redir, vars);
	vars->pid[0] = fork();
	if (vars->pid[0] == -1)
		return (FAILURE);
	if (vars->pid[0] == 0)
		ft_exec_redir_child(vars);
	waitpid(vars->pid[0], &vars->status, 0);
	g_check = 0;
	return (SUCCESS);
}

int	ft_exec_pipe_redir_parent(t_vars *vars)
{
	size_t	i;

	g_check = 1;
	ft_nb_redir_type(vars->redir, vars);
	while (vars->i < vars->nb)
	{
		vars->pid[vars->i] = fork();
		if (vars->pid[vars->i] == -1)
			return (FAILURE);
		if (vars->pid[vars->i] == 0)
			ft_exec_pipe_file_child(vars);
		vars->i++;
	}
	ft_close_pipes(vars->pipes, (vars->nb - 1));
	i = 0;
	while (i < vars->nb)
		waitpid(vars->pid[i++], &vars->status, 0);
	g_check = 0;
	return (SUCCESS);
}
