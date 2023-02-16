/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/02/14 12:28:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 10:42:08 by obouhlel         ###   ########.fr       */
=======
/*   Created: 2023/02/01 10:04:12 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/03 12:21:32 by pjay             ###   ########.fr       */
>>>>>>> origin/pjay
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

<<<<<<< HEAD
int	main_exec(t_list *lst, char **env)
{
	t_vars	*vars;
	int		status;

	vars = ft_init_vars(lst, env);
	if (!vars)
		return (EXIT_FAILURE);
	if (vars->nb == 1 && vars->nb_redir == 0)
		status = ft_exec(vars);
	else if (vars->nb > 1 && vars->nb_redir == 0)
		status = ft_exec_pipe(vars);
	else if (vars->nb == 1 && vars->nb_redir > 0)
		status = ft_exec_redir(vars);
	else if (vars->nb > 1 && vars->nb_redir > 0)
		status = ft_exec_pipe_redir(vars);
	if (status == FAILURE)
	{
		ft_putendl_fd("minishell: fork failed", STDERR);
		ft_free_vars(vars);
		return (EXIT_FAILURE);
	}
	ft_free_vars(vars);
	return (EXIT_SUCCESS);
}

int	ft_exec(t_vars *vars)
{
	vars->pid[0] = fork();
	if (vars->pid[0] == -1)
		return (FAILURE);
	if (vars->pid[0] == 0)
		ft_exec_child(vars);
	waitpid(vars->pid[0], &vars->status, 0);
	return (SUCCESS);
}

int	ft_exec_pipe(t_vars *vars)
{
	size_t	i;

	while (vars->i < vars->nb)
	{
		vars->pid[vars->i] = fork();
		if (vars->pid[vars->i] == -1)
			return (FAILURE);
		if (vars->pid[vars->i] == 0)
			ft_exec_pipe_child(vars);
		vars->i++;
	}
	ft_close_pipes(vars->pipes, (vars->nb - 1));
	i = 0;
	while (i < vars->nb)
		waitpid(vars->pid[i++], &vars->status, 0);
	return (SUCCESS);
}

int	ft_exec_redir(t_vars *vars)
{
	ft_nb_redir_type(vars->redir, vars);
	vars->pid[0] = fork();
	if (vars->pid[0] == -1)
		return (FAILURE);
	if (vars->pid[0] == 0)
		ft_exec_redir_child(vars);
	waitpid(vars->pid[0], &vars->status, 0);
	return (SUCCESS);
}

int	ft_exec_pipe_redir(t_vars *vars)
{
	size_t	i;

	ft_nb_redir_type(vars->redir, vars);
	while (vars->i < vars->nb)
	{
		vars->pid[vars->i] = fork();
		if (vars->pid[vars->i] == -1)
			return (FAILURE);
		if (vars->pid[vars->i] == 0)
			ft_exec_pipe_file_child(vars);
		vars->i++;
	}
	ft_close_pipes(vars->pipes, (vars->nb - 1));
	i = 0;
	while (i < vars->nb)
		waitpid(vars->pid[i++], &vars->status, 0);
	return (SUCCESS);
}
=======
// int	main(int ac, char **av, char **envp)
// {
// 	t_list	*cmd;

// 	cmd = NULL;
// 	(void)envp;
// 	if (ac == 1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		ft_putendl_fd("command not found", STDERR_FILENO);
// 	}
// 	else
// 	{
// 		cmd = ft_lstnew(av[1]);
// 		ft_lstadd_back(&cmd, ft_lstnew(av[2]));
// 		ft_lstadd_back(&cmd, ft_lstnew(av[3]));
// 		ft_echo_exec(cmd);
// 	}
// 	ft_lstclear(&cmd, delete_content);
// 	return (EXIT_SUCCESS);
// }
>>>>>>> origin/pjay
