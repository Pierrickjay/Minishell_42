/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:28:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 18:47:14 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	if (!envp)
		return (ft_msg(exec, NULL, MA, NULL), NULL);
	exit_code = exec->status;
	ft_free_exec(exec);
	return (envp);
}

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
			return (ft_msg(exec, NULL, MA, NULL), EXIT_FAILURE);
		ft_msg(exec, NULL, errno, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

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
				return (ft_msg(NULL, NULL, MA, NULL));
			exec->envi = ft_envi_update_value("SHLVL", shlvl, 0, exec->envi);
			exec->env = ft_envi_to_env(exec->envi);
			if (!exec->env)
				return (ft_msg(NULL, NULL, MA, NULL));
			free(shlvl);
		}
		update = true;
	}
}
