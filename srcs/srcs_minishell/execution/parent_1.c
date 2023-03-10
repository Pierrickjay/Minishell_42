/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:09:06 by pjay              #+#    #+#             */
/*   Updated: 2023/03/10 18:38:50 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// main execution, the big boss
t_envi	*main_exec(t_list *lst, t_envi *envi, int *count_line, int *exit_code)
{
	t_exec		*exec;
	t_envi		*envp;

	ft_lst_print_type(lst);
	if (check_redir_nb(lst) == -1 || check_arrow_pipe(lst) == -1 \
		|| check_next_arrow(lst) == -1 || check_pipe(lst) == -1)
	{
		*exit_code = 2;
		return (envi);
	}
	if (ft_get_vars(envi, lst, *exit_code))
		return (ft_free_lst(lst), ft_msg_malloc("parent_1.c (30)"), envi);
	exec = ft_init_exec(lst, envi, count_line);
	if (!exec)
		return (NULL);
	ft_update_shlvl(exec);
	if (ft_parent_bis(exec, envi))
		return (envi);
	envp = ft_dup_envi(exec->envi);
	if (envp == FAIL)
		return (ft_free_exec(exec), NULL);
	ft_exit_code(exec);
	*exit_code = exec->status;
	return (ft_free_exec(exec), envp);
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
int	ft_parent_bis(t_exec *exec, t_envi *envp)
{
	int	status;

	status = 0;
	if (exec->nb == 0 && exec->nb_redir > 0)
		status = ft_exec_parent_no_cmd(exec);
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
	else if (exec->status == 512 || exec->status == 5120)
		exec->status = 127;
	else
	{
		if (exec->status > 255)
		{
			while (exec->status > 255)
				exec->status -= 256;
		}
	}
}
