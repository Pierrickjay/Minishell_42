/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:21:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 15:19:40 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	ft_exit_not_num(t_list *list, t_envi *envp)
{
	if (list->next && list->next->content && \
		!ft_all_isdigit(list->next->content))
	{
		ft_putstr_fd("exit: ", STDERR);
		ft_putstr_fd(list->next->content, STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		if (envp)
			ft_free_envi(envp);
		ft_free_lst(list);
		exit(2);
	}
}

void	ft_exit(t_list *list, t_envi *envp, char **split, char *save)
{
	int	exit_value;

	exit_value = 0;
	free(split);
	free(save);
	if (ft_strcmp(list->content, "exit") == 0)
	{
		ft_putendl_fd("exit", STDOUT);
		ft_exit_not_num(list, envp);
		if (list->next && list->next->next)
			return ;
		if (list->next && list->next->content && \
			ft_all_isdigit(list->next->content))
			exit_value = ft_atoi(list->next->content);
		if (envp)
			ft_free_envi(envp);
		ft_free_lst(list);
		while (exit_value > 255)
			exit_value -= 256;
		exit(exit_value);
	}
}

// static int	ft_check_exit(t_list *lst, int *exit_value)
// {
// 	const size_t	size = ft_lstsize(lst);

// 	if (size == 1)
// 		return (EXIT_SUCCESS);
// 	else if (size == 2)
// 	{
// 		lst = lst->next;
// 		if (ft_all_isdigit(lst->content) == 0)
// 		{
// 			*exit_value = ft_atoi(lst->content);
// 			return (EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			ft_putstr_fd(lst->content, STDERR);
// 			ft_putendl_fd(": numeric argument required", STDERR);
// 			return (EXIT_SUCCESS);
// 		}
// 	}
// 	return (EXIT_FAILURE);
// }

// void	ft_exit(t_list *list, t_envi *envp, char **split, char *save)
// {
// 	int	exit_value;

// 	exit_value = 0;
// 	free(split);
// 	free(save);
// 	if (ft_strcmp(list->content, "exit") == 0)
// 	{
// 		ft_putendl_fd("exit", STDOUT);
// 		if (ft_check_exit(list, &exit_value))
// 			return ;
// 		if (envp)
// 			ft_free_envi(envp);
// 		ft_free_lst(list);
// 		while (exit_value > 255)
// 			exit_value -= 256;
// 		exit(exit_value);
// 	}
// }
