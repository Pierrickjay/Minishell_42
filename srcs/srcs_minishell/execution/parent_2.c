/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:31:57 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:16:43 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// execution for no command and with redirection
int	ft_shell_parent_no_cmd(t_shell *shell)
{
	pid_t	*pid;

	pid = malloc(sizeof(*pid));
	if (pid == NULL)
		return (FAILURE);
	shell->pid = pid;
	*pid = fork();
	if (*pid == -1)
		return (FAILURE);
	if (*pid == 0)
	{
		create_siga(CHILD);
		ft_shell_child_no_cmd(shell);
	}
	waitpid(*pid, &shell->status, WUNTRACED);
	deal_w_return_pid(shell->status);
	return (SUCCESS);
}

// child for one command and no redirection
int	ft_shell_parent(t_shell *shell)
{
	if (builtins_in_parent(shell) == FAILURE)
	{
		shell->pid[0] = fork();
		if (shell->pid[0] == -1)
			return (FAILURE);
		if (shell->pid[0] == 0)
		{
			create_siga(CHILD);
			ft_shell_child(shell);
		}
	}
	waitpid(shell->pid[0], &shell->status, WUNTRACED);
	if (shell->status == 2)
		shell->status = 130;
	deal_w_return_pid(shell->status);
	return (SUCCESS);
}

// child for n commands and no redirection
int	ft_shell_pipe_parent(t_shell *shell)
{
	int	i;

	while (shell->id_child < shell->nb_cmd)
	{
		if (builtins_in_parent(shell) == FAILURE)
		{
			shell->pid[shell->id_child] = fork();
			if (shell->pid[shell->id_child] == -1)
				return (FAILURE);
			if (shell->pid[shell->id_child] == 0)
			{
				create_siga(CHILD);
				ft_shell_pipe_child(shell);
			}
		}
		shell->id_child++;
	}
	ft_close_pipes(shell->pipes, (shell->nb_cmd - 1));
	i = 0;
	while (i < shell->nb_cmd)
		waitpid(shell->pid[i++], &shell->status, 0);
	return (SUCCESS);
}

// child for one command and redirection
int	ft_shell_redir_parent(t_shell *shell)
{
	if (builtins_in_parent(shell) == FAILURE)
	{
		shell->pid[0] = fork();
		if (shell->pid[0] == -1)
			return (FAILURE);
		if (shell->pid[0] == 0)
		{
			create_siga(CHILD);
			ft_shell_redir_child(shell);
		}
	}
	waitpid(shell->pid[0], &shell->status, 0);
	return (SUCCESS);
}

// child for n commands and redirection
int	ft_shell_pipe_redir_parent(t_shell *shell)
{
	int	i;

	while (shell->id_child < shell->nb_cmd)
	{
		if (builtins_in_parent(shell) == FAILURE)
		{
			shell->pid[shell->id_child] = fork();
			if (shell->pid[shell->id_child] == -1)
				return (FAILURE);
			if (shell->pid[shell->id_child] == 0)
			{
				create_siga(CHILD);
				ft_shell_pipe_file_child(shell);
			}
		}
		shell->id_child++;
	}
	ft_close_pipes(shell->pipes, (shell->nb_cmd - 1));
	i = 0;
	while (i < shell->nb_cmd)
		waitpid(shell->pid[i++], &shell->status, 0);
	return (SUCCESS);
}
