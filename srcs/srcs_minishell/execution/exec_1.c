/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:43:42 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 12:39:54 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_exec	*ft_init_exec(t_list *lst, t_envi *envi, int exit_code)
{
	t_exec	*exec;

	exec = NULL;
	exec = (t_exec *)ft_calloc(sizeof(t_exec), 1);
	if (!exec)
		return (ft_msg(NULL, NULL, MA, NULL), NULL);
	exec->lst = lst;
	exec->env = ft_envi_to_env(envi);
	if (!exec->env)
		return (ft_msg(exec, NULL, MA, NULL), NULL);
	exec->envi = envi;
	if (ft_get_vars(exec, exit_code) == EXIT_FAILURE)
		return (ft_msg(exec, NULL, MA, NULL), NULL);
	exec->nb = ft_nb_cmds(lst);
	exec->nb_redir = ft_nb_redir(lst);
	exec->redir = ft_lst_redir(lst);
	if (!exec->redir && exec->nb_redir > 0)
		return (ft_msg(exec, NULL, MA, NULL), NULL);
	if (exec->nb > 0 && ft_init_exec_bis(exec, lst) == FAILURE)
		return (NULL);
	return (exec);
}

int	ft_init_exec_bis(t_exec *exec, t_list *lst)
{
	exec->pid = ft_init_pid(exec);
	if (!exec->pid)
		return (FAILURE);
	exec->args = ft_init_args(exec, lst);
	if (!exec->args)
		return (FAILURE);
	exec->pipes = ft_init_pipes(exec);
	if (exec->pipes == FAIL)
		return (FAILURE);
	return (SUCCESS);
}

pid_t	*ft_init_pid(t_exec *exec)
{
	pid_t	*pid;
	int		i;

	pid = NULL;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), exec->nb);
	if (!pid)
		return (ft_msg(exec, NULL, MA, NULL), NULL);
	i = 0;
	while (i < exec->nb)
	{
		pid[i] = 0;
		i++;
	}
	return (pid);
}

int	**ft_init_pipes(t_exec *exec)
{
	int		**pipes;
	int		i;

	pipes = NULL;
	if (exec->nb == 1)
		return (NULL);
	pipes = (int **)ft_calloc(sizeof(int *), (exec->nb - 1));
	if (!pipes)
		return (ft_msg(exec, NULL, MA, NULL), FAIL);
	i = -1;
	while (++i < (exec->nb - 1))
	{
		pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!pipes[i])
			return (ft_free_pipes(pipes, (int)i), \
					ft_close_pipes(pipes, (exec->nb - 1)), \
					ft_msg(exec, NULL, MA, NULL), FAIL);
	}
	i = -1;
	while (++i < (exec->nb - 1))
		if (pipe(pipes[i]) == -1)
			return (ft_close_pipes(pipes, (exec->nb - 1)), \
					ft_msg(exec, "pipes: ", errno, NULL), FAIL);
	return (pipes);
}

char	***ft_init_args(t_exec *exec, t_list *lst)
{
	char	***args;
	int		i;
	int		skip;

	args = NULL;
	args = (char ***)ft_calloc(sizeof(char **), (exec->nb + 1));
	if (!args)
		return (ft_msg(exec, NULL, MA, NULL), NULL);
	i = 0;
	while (i < exec->nb)
	{
		args[i] = ft_lst_to_args(lst);
		if (!args[i])
			return (ft_free_args(args, i), \
					ft_msg(exec, NULL, MA, NULL), NULL);
		while (lst && lst->type != CMD)
			lst = lst->next;
		skip = ft_args_size(lst) + 1;
		while (lst && skip--)
			lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
