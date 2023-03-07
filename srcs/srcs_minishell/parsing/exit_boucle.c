/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_boucle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:49:30 by pjay              #+#    #+#             */
/*   Updated: 2023/03/07 09:10:35 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	save_is_null(char *save, t_envi *envp)
{
	if (save == NULL)
	{
		ft_putendl_fd("exit", STDOUT);
		ft_free_envi(envp);
		exit(0);
	}
	if (save[0] == '\0')
	{
		free(save);
		return (-1);
	}
	return (0);
}

void	free_all(char **split, char *save)
{
	ft_free((void **)&save);
	free(split);
}

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

void	ft_exit(t_list *list, t_envi *envp)
{
	int	exit_value;

	exit_value = 0;
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

int	ft_check_list(t_list *list, t_free *to_free, char *save, t_envi *envp)
{
	if (list == NULL)
	{
		free_all(to_free->split, save);
		ft_free_envi(envp);
		ft_free_lst(list);
		ft_putendl_fd("exit", STDOUT);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
