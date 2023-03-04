/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_boucle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:49:30 by pjay              #+#    #+#             */
/*   Updated: 2023/03/03 09:50:58 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_all(char **split, char *save)
{
	free(save);
	free(split);
}

int	save_is_null(char *save)
{
	if (save == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (save[0] == '\0')
	{
		free(save);
		return (-1);
	}
	return (0);
}

void	ft_exit(t_list *list, char *save, char **envp)
{
	if (ft_strcmp(list->content, "exit") == 0)
	{
		free(save);
		ft_free_lst(list);
		ft_free_strs(envp);
		ft_putendl_fd("exit", STDOUT);
		exit(0);
	}
}

int	ft_check_list(t_list *list, t_free *to_free, char *save, char **envp)
{
	if (list == NULL)
	{
		free_all(to_free->split, save);
		ft_free_strs(envp);
		ft_free_lst(list);
		ft_putendl_fd("exit", STDOUT);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
