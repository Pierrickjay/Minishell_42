/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:43:42 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 11:45:26 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_vars	*ft_init_vars(t_list *lst, char **env)
{
	t_vars	*vars;

	vars = NULL;
	vars = (t_vars *)ft_calloc(sizeof(t_vars), 1);
	if (!vars)
		return (NULL);
	vars->lst = lst;
	vars->env = env;
	vars->i = 0;
	vars->nb = ft_nb_cmds(lst);
	vars->nb_redir = ft_nb_redir(lst);
	vars->redir = ft_lst_redir(lst);
	if (!vars->redir && vars->nb_redir > 0)
		return (ft_free_vars(vars), NULL);
	vars->pid = ft_init_pid(vars);
	if (vars->pid == FAIL)
		return (ft_free_vars(vars), NULL);
	vars->pipes = ft_init_pipes(vars);
	if (vars->pipes == FAIL)
		return (ft_free_vars(vars), NULL);
	vars->args = ft_init_args(vars, lst);
	if (!vars->args)
		return (ft_free_vars(vars), NULL);
	vars->status = 0;
	return (vars);
}

pid_t	*ft_init_pid(t_vars *vars)
{
	pid_t	*pid;
	size_t	i;

	pid = NULL;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), vars->nb);
	if (!pid)
		return (FAIL);
	i = 0;
	while (i < vars->nb)
	{
		pid[i] = 0;
		i++;
	}
	return (pid);
}

int	**ft_init_pipes(t_vars *vars)
{
	int		**pipes;
	size_t	i;

	pipes = NULL;
	if (vars->nb == 1)
		return (NULL);
	pipes = (int **)ft_calloc(sizeof(int *), (vars->nb - 1));
	if (!pipes)
		return (FAIL);
	i = 0;
	while (i < (vars->nb - 1))
	{
		pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!pipes[i])
			return (FAIL);
		i++;
	}
	i = 0;
	while (i < (vars->nb - 1))
	{
		if (pipe(pipes[i]) == -1)
			return (FAIL);
		i++;
	}
	return (pipes);
}

char	***ft_init_args(t_vars *vars, t_list *lst)
{
	char	***args;
	size_t	i;
	size_t	skip;

	args = NULL;
	args = (char ***)ft_calloc(sizeof(char **), (vars->nb + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i < vars->nb)
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
