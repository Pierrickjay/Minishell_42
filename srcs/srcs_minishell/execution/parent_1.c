/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:28:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 12:52:05 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**main_exec(t_list *lst, char **env)
{
	t_exec	*exec;
	char	**envp;
	int		status;

	status = 0;
	exec = ft_init_exec(lst, env);
	if (!exec)
		return (NULL);
	if (exec->nb == 0)
		return (ft_putendl_fd(SYNTAX, 2), ft_free_exec(exec), env);
	if (exec->nb == 1 && exec->nb_redir == 0)
		status = ft_exec_parent(exec);
	else if (exec->nb > 1 && exec->nb_redir == 0)
		status = ft_exec_pipe_parent(exec);
	else if (exec->nb == 1 && exec->nb_redir > 0)
		status = ft_exec_redir_parent(exec);
	else if (exec->nb > 1 && exec->nb_redir > 0)
		status = ft_exec_pipe_redir_parent(exec);
	if (ft_check_status(status, exec, &envp) == FAILURE)
		return (envp);
	envp = ft_dup_env(exec->env);
	ft_free_exec(exec);
	return (envp);
}

int	ft_check_status(int status, t_exec *exec, char ***envp)
{
	if (status == FAILURE)
	{
		ft_putendl_fd("minishell: fork failed", STDERR);
		*envp = ft_dup_env(exec->env);
		ft_free_exec(exec);
	}
	return (SUCCESS);
}
