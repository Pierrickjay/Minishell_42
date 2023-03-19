/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:21:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:27:50 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// check if the argument is a digit or not
static void	ft_exit_alpha_args(t_list *list, t_envi *envp)
{
	const int	nb_cmds = ft_nb_cmds(list);

	if (ft_strcmp("exit", list->content) == 0)
	{
		if (list->next && list->next->content)
		{
			if (ft_all_isdigit(list->next->content) && nb_cmds == 1)
			{
				ft_putendl_fd("exit", STDERR);
				ft_putstr_fd("exit: ", STDERR);
				ft_putstr_fd(list->next->content, STDERR);
				ft_putendl_fd(": numeric argument required", STDERR);
				if (envp)
					ft_free_envi(envp);
				ft_free_lst(list);
				exit(2);
			}
		}
	}
}

// exit function check the arguments
void	ft_exit(t_list *list, t_envi *envp, t_free *to_free, char *save)
{
	const size_t	size = ft_lstsize(list);
	int				exit_value;

	exit_value = 0;
	free(to_free->not_expend);
	free(to_free->newsplit);
	free(to_free->is_in_quote);
	free(save);
	ft_exit_alpha_args(list, envp);
	if (ft_strcmp(list->content, "exit") == 0 && size <= 2)
	{
		if (list->next && list->next->content)
			exit_value = ft_atoi(list->next->content);
		ft_putendl_fd("exit", STDERR);
		if (envp)
			ft_free_envi(envp);
		ft_free_lst(list);
		while (exit_value > 255)
			exit_value -= 256;
		exit(exit_value);
	}
}
