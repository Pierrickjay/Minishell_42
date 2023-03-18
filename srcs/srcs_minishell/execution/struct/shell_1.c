/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:33:35 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 20:16:17 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// initialize shell struct
t_shell	*init_shell(t_list *lst, t_envi *envi, int *countline, int *exitcode)
{
	t_shell	*shell;

	shell = NULL;
	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (ft_msg_malloc("shell_1.c (23)"), NULL);
	shell->lst = lst;
	shell->env = ft_envi_to_env(envi);
	if (shell->env == FAIL)
		return (ft_msg(shell, "shell_1.c (27)", MA, NULL), NULL);
	shell->envi = envi;
	shell->count_line = countline;
	shell->exit_code = exitcode;
	shell->nb_cmd = ft_nb_cmds(lst);
	shell->nb_redir = ft_nb_redir(lst);
	if (ft_lst_redir_malloc(shell, lst))
		return (ft_msg(shell, "shell_1.c (33)", MA, NULL), NULL);
	if (!shell->redir && shell->nb_redir > 0)
		return (ft_msg(shell, "shell_1.c (36)", MA, NULL), NULL);
	if (shell->nb_cmd > 0 && init_shell_bis(shell, lst) == FAILURE)
		return (NULL);
	return (shell);
}

// initialize shell struct bis
int	init_shell_bis(t_shell *shell, t_list *lst)
{
	shell->pid = ft_init_pid(shell);
	if (!shell->pid)
		return (FAILURE);
	shell->args = ft_init_args(shell, lst);
	if (!shell->args)
		return (FAILURE);
	shell->pipes = ft_init_pipes(shell);
	if (shell->pipes == FAIL)
		return (FAILURE);
	return (SUCCESS);
}

// initialize pid array
pid_t	*ft_init_pid(t_shell *shell)
{
	pid_t	*pid;
	int		i;

	pid = NULL;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), shell->nb_cmd);
	if (!pid)
		return (ft_msg(shell, "shell_1.c (65)", MA, NULL), NULL);
	i = 0;
	while (i < shell->nb_cmd)
	{
		pid[i] = 0;
		i++;
	}
	return (pid);
}

// initialize pipes array
int	**ft_init_pipes(t_shell *shell)
{
	int		**pipes;
	int		i;

	pipes = NULL;
	if (shell->nb_cmd == 1)
		return (NULL);
	pipes = (int **)ft_calloc(sizeof(int *), (shell->nb_cmd - 1));
	if (!pipes)
		return (ft_msg(shell, "shell_1.c (86)", MA, NULL), FAIL);
	i = -1;
	while (++i < (shell->nb_cmd - 1))
	{
		pipes[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!pipes[i])
			return (ft_free_pipes(pipes, (int)i), \
					ft_close_pipes(pipes, (shell->nb_cmd - 1)), \
					ft_msg(shell, "shell_1.c (94)", MA, NULL), FAIL);
	}
	i = -1;
	while (++i < (shell->nb_cmd - 1))
		if (pipe(pipes[i]) == -1)
			return (ft_close_pipes(pipes, (shell->nb_cmd - 1)), \
					ft_msg(shell, "pipes: ", errno, NULL), FAIL);
	return (pipes);
}

// initialize args array
char	***ft_init_args(t_shell *shell, t_list *lst)
{
	char	***args;
	int		i;
	int		skip;

	args = NULL;
	args = (char ***)ft_calloc(sizeof(char **), (shell->nb_cmd + 1));
	if (!args)
		return (ft_msg(shell, "shell_1.c (114)", MA, NULL), NULL);
	i = 0;
	while (i < shell->nb_cmd)
	{
		args[i] = ft_lst_to_args(lst);
		if (!args[i])
			return (ft_free_args(args, i), \
					ft_msg(shell, "shell_1.c (121)", MA, NULL), NULL);
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
