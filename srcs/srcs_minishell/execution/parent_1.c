/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:17:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 14:18:38 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// main execution, the big boss
t_envi	*main_exec(t_list *lst, t_envi *envi)
{
	static int	exit_code = 0;
	t_exec		*exec;
	t_envi		*envp;

	if (check_redir_nb(lst) == -1 || check_arrow_pipe(lst) == -1)
	{
		exit_code = 2;
		return (envi);
	}
	if (ft_get_vars(envi, lst, exit_code))
		return (ft_free_lst(lst), ft_msg_malloc("parent_1.c (30)"), envi);
	if (ft_check_lst_cmds_here_doc(lst, &exit_code))
		return (envi);
	exec = ft_init_exec(lst, envi);
	if (!exec)
		return (NULL);
	ft_update_shlvl(exec);
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

//for check if have cmd
int	ft_check_lst_cmds_here_doc(t_list *lst, int *exit_code)
{
	int		fd;
	size_t	nb_cmds;

	nb_cmds = ft_nb_cmds(lst);
	if (nb_cmds == 0)
	{
		*exit_code = 0;
		while (lst)
		{
			if (lst->type == REDIR && !ft_strcmp("<<", lst->content) \
				&& lst->next)
			{
				*exit_code = 1;
				fd = ft_open(lst->next->content, HEREDOC);
				if (fd == FAILURE)
					return (ft_msg(NULL, NULL, errno, NULL), EXIT_FAILURE);
				ft_close(&fd);
			}
			lst = lst->next;
		}
	}
	return (EXIT_SUCCESS);
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
	else
	{
		if (exec->status > 255)
		{
			while (exec->status > 255)
				exec->status -= 256;
		}
	}
}
