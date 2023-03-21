/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:09:06 by pjay              #+#    #+#             */
/*   Updated: 2023/03/21 12:15:14 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// main execution, the big boss
t_envi	*main_exec(t_list *lst, t_envi *envi, int *count_line, int *exit_code)
{
	t_shell		*shell;
	t_envi		*envp;

	if (check_redir_nb(lst) == -1 || check_arrow_pipe(lst) == -1 \
		|| check_next_arrow(lst) == -1 || check_pipe(lst) == -1)
	{
		*exit_code = 2;
		return (envi);
	}
	if (run_heredoc(lst, envi, count_line, exit_code))
		return (ft_free_lst(lst), envi);
	if (ft_lst_expend(envi, lst, *exit_code))
		return (ft_free_lst(lst), ft_msg_malloc("parent_1.c (30)"), envi);
	shell = init_shell(lst, envi, count_line, exit_code);
	if (!shell)
		return (NULL);
	ft_update_shlvl(shell);
	if (ft_parent_bis(shell, envi))
		return (envi);
	envp = ft_dup_envi(shell->envi);
	if (envp == FAIL)
		return (ft_free_shell(shell), NULL);
	ft_exit_code(shell);
	*exit_code = shell->status;
	return (ft_free_shell(shell), envp);
}

// exit code for signal
void	deal_w_return_pid(int status)
{
	if (status == 130)
		ft_putchar_fd('\n', STDERR);
	else if (status == 131)
		ft_putendl_fd("Quit (core dumped)", STDERR);
	else
		return ;
}

// parent call the child
int	ft_parent_bis(t_shell *shell, t_envi *envp)
{
	int	status;

	status = 0;
	if (shell->nb_cmd == 0 && shell->nb_redir > 0)
		status = ft_shell_parent_no_cmd(shell);
	if (shell->nb_cmd == 1 && shell->nb_redir == 0)
		status = ft_shell_parent(shell);
	else if (shell->nb_cmd > 1 && shell->nb_redir == 0)
		status = ft_shell_pipe_parent(shell);
	else if (shell->nb_cmd == 1 && shell->nb_redir > 0)
		status = ft_shell_redir_parent(shell);
	else if (shell->nb_cmd > 1 && shell->nb_redir > 0)
		status = ft_shell_pipe_redir_parent(shell);
	if (status == FAILURE)
	{
		envp = ft_dup_envi(shell->envi);
		if (!envp)
			return (ft_msg(shell, "parent_1.c (60)", MA, NULL), EXIT_FAILURE);
		ft_msg(shell, NULL, errno, NULL);
		return (EXIT_FAILURE);
	}
	ft_unlink(shell->lst);
	return (EXIT_SUCCESS);
}

// update the SHLVL variable
void	ft_update_shlvl(t_shell *shell)
{
	static int	update = false;
	char		*shlvl;
	int			nb;

	if (update == false)
	{
		shlvl = ft_getenvi("SHLVL", shell->envi);
		if (shlvl)
		{
			ft_free_strs(shell->env);
			nb = ft_atoi(shlvl);
			nb++;
			shlvl = ft_itoa(nb);
			if (!shlvl)
				return (ft_msg_malloc("parent_1.c (84)"));
			shell->envi = ft_envi_update_value("SHLVL", shlvl, 0, shell->envi);
			shell->env = ft_envi_to_env(shell->envi);
			if (shell->env == FAIL)
				return (ft_msg_malloc("parent_1.c (88)"));
			free(shlvl);
		}
		update = true;
	}
}

// update the exit code
void	ft_exit_code(t_shell *shell)
{
	if (shell->status == 64512)
		shell->status = 127;
	if (shell->status == 65280)
		shell->status = 1;
	else if (shell->status == 64256)
		shell->status = 128;
	else if (shell->status == 5120)
		shell->status = 127;
	else
	{
		if (shell->status > 255)
		{
			while (shell->status > 255)
				shell->status -= 255;
		}
	}
}
