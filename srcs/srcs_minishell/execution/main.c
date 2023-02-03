/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:12 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/03 12:21:32 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
