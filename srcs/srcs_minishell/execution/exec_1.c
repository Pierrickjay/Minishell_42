/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:43:42 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/25 16:25:58 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_exec	*ft_init_exec(t_list *lst, char **env)
{
	t_exec	*exec;

	exec = NULL;
	exec = (t_exec *)ft_calloc(sizeof(t_exec), 1);
	if (!exec)
		return (NULL);
	exec->lst = lst;
	exec->env = env;
	if (!exec->env)
		return (ft_free_exec(exec), NULL);
	exec->envi = ft_env_to_envi(env);
	if (!exec->envi)
		return (ft_free_exec(exec), NULL);
	if (ft_get_vars(exec) == EXIT_FAILURE)
		return (ft_free_exec(exec), NULL);
	exec->nb = ft_nb_cmds(lst);
	exec->nb_redir = ft_nb_redir(lst);
	exec->redir = ft_lst_redir(lst);
	if (!exec->redir && exec->nb_redir > 0)
		return (ft_free_exec(exec), NULL);
	if (exec->nb > 0 && ft_init_exec_bis(exec, lst) == NULL)
		return (ft_free_exec(exec), NULL);
	return (exec);
}

void	*ft_init_exec_bis(t_exec *exec, t_list *lst)
{
	exec->pid = ft_init_pid(exec);
	if (exec->pid == FAIL)
		return (ft_free_exec(exec), NULL);
	exec->pipes = ft_init_pipes(exec);
	if (exec->pipes == FAIL)
		return (ft_free_exec(exec), NULL);
	exec->args = ft_init_args(exec, lst);
	if (!exec->args)
		return (ft_free_exec(exec), NULL);
	return ((void *)1);
}

pid_t	*ft_init_pid(t_exec *exec)
{
	pid_t	*pid;
	size_t	i;

	pid = NULL;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), exec->nb);
	if (!pid)
		return (FAIL);
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
	size_t	i;

	pipes = NULL;
	if (exec->nb == 1)
		return (NULL);
	pipes = (int **)ft_calloc(sizeof(int *), (exec->nb - 1));
	if (!pipes)
		return (FAIL);
	i = 0;
	while (i < (exec->nb - 1))
	{
		pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!pipes[i])
			return (FAIL);
		i++;
	}
	i = 0;
	while (i < (exec->nb - 1))
	{
		if (pipe(pipes[i]) == -1)
			return (FAIL);
		i++;
	}
	return (pipes);
}

char	***ft_init_args(t_exec *exec, t_list *lst)
{
	char	***args;
	size_t	i;
	size_t	skip;

	args = NULL;
	args = (char ***)ft_calloc(sizeof(char **), (exec->nb + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i < exec->nb)
	{
		args[i] = ft_lst_to_args(lst);
		if (!args[i])
			return (NULL);
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
