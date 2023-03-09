/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:21:54 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 10:22:40 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	ft_exit_bis(t_list *list, t_envi *envp)
{
	if (list->next && list->next->content && \
		ft_isalpha(list->next->content[0]))
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
		ft_exit_bis(list, envp);
		if (list->next && list->next->next && \
			ft_isdigit(list->next->next->content[0]) == 1)
			return ;
		if (list->next && list->next->content && \
			ft_isdigit(list->next->content[0]))
			exit_value = ft_atoi(list->next->content);
		ft_putendl_fd("exit", STDOUT);
		if (envp)
			ft_free_envi(envp);
		ft_free_lst(list);
		while (exit_value > 255)
			exit_value -= 256;
		exit(exit_value);
	}
}
