/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_boucle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:49:30 by pjay              #+#    #+#             */
/*   Updated: 2023/03/07 11:07:31 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	save_is_null(char *save, t_envi *envp)
{
	if (save == NULL)
	{
		printf("exit\n");
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
	free(save);
	free(split);
}

void	ft_exit(t_list *list, char *save, t_envi *envp, t_free *to_free)
{
	int	exit_value;

	exit_value = 0;
	if (ft_strcmp(list->content, "exit") == 0)
	{
		if (list->next && list->next->next && \
			ft_isdigit(list->next->next->content[0]) == 1)
			return ;
		if (list->next && list->next->content)
			exit_value = ft_atoi(list->next->content);
		free_all(to_free->split, save);
		ft_free_lst(list);
		ft_free_envi(envp);
		ft_putendl_fd("exit", STDOUT);
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
