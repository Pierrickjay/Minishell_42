/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:28:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 11:05:57 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// main execution, the big boss
t_envi	*main_exec(t_list *lst, t_envi *envi)
{
	static int	exit_code = 0;
	t_exec		*exec;
	t_envi		*envp;

	exec = ft_init_exec(lst, envi, exit_code);
	if (!exec)
		return (NULL);
	ft_update_shlvl(exec);
	if (exec->nb == 0)
	{
		envp = ft_dup_envi(exec->envi);
		return (ft_msg(exec, NULL, SY, NULL), envp);
	}
	if (ft_parent_bis(exec, envi))
		return (envi);
	envp = ft_dup_envi(exec->envi);
	if (envp == FAIL)
		return (ft_free_exec(exec), NULL);
	ft_exit_code(exec);
	exit_code = exec->status;
	ft_free_exec(exec);
	return (envp);
}

// parent call the child
int	ft_parent_bis(t_exec *exec, t_envi *envp)
{
	int	status;

	status = 0;
	if (exec->nb == 1 && exec->nb_redir == 0)
		status = ft_exec_parent(exec);
	else if (exec->nb > 1 && exec->nb_redir == 0)
		status = ft_exec_pipe_parent(exec);
	else if (exec->nb == 1 && exec->nb_redir > 0)
		status = ft_exec_redir_parent(exec);
	else if (exec->nb > 1 && exec->nb_redir > 0)
		status = ft_exec_pipe_redir_parent(exec);
	if (status == FAILURE)
	{
		envp = ft_dup_envi(exec->envi);
		if (!envp)
			return (ft_msg(exec, "parent_1.c (60)", MA, NULL), EXIT_FAILURE);
		ft_msg(exec, NULL, errno, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// update the SHLVL variable
void	ft_update_shlvl(t_exec *exec)
{
	static int	update = false;
	char		*shlvl;
	int			nb;

	if (update == false)
	{
		shlvl = ft_getenvi("SHLVL", exec->envi);
		if (shlvl)
		{
			ft_free_strs(exec->env);
			nb = ft_atoi(shlvl);
			nb++;
			shlvl = ft_itoa(nb);
			if (!shlvl)
				return (ft_msg_malloc("parent_1.c (84)"));
			exec->envi = ft_envi_update_value("SHLVL", shlvl, 0, exec->envi);
			exec->env = ft_envi_to_env(exec->envi);
			if (exec->env == FAIL)
				return (ft_msg_malloc("parent_1.c (88)"));
			free(shlvl);
		}
		update = true;
	}
}

// update the exit code
void	ft_exit_code(t_exec *exec)
{
	if (exec->status == 64512)
		exec->status = 127;
	else if (exec->status == 65280)
		exec->status = 1;
	else if (exec->status == 64256)
		exec->status = 128;
	else if (exec->status == 256)
		exec->status = 1;
}
