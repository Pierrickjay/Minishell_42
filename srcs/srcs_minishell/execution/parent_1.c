/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:28:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 13:05:07 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**main_exec(t_list *lst, char **env)
{
	static int	exit_code;
	t_exec		*exec;
	char		**envp;

	exec = ft_init_exec(lst, env);
	if (!exec)
		return (NULL);
	if (exec->nb == 0)
	{
		envp = ft_dup_env(env);
		return (ft_close_pipes(exec->pipes, (exec->nb - 1)), \
				ft_msg(exec, NULL, SY, NULL), envp);
	}
	if (ft_parent_bis(exec, &envp))
		return (envp);
	envp = ft_dup_env(exec->env);
	exit_code = exec->status;
	printf("Exit code = %d\n", exit_code);
	ft_free_exec(exec);
	return (envp);
}

int	ft_parent_bis(t_exec *exec, char ***envp)
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
		*envp = ft_dup_env(exec->env);
		ft_msg(exec, NULL, errno, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
