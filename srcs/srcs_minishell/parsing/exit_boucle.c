/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_boucle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:28:44 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 15:28:45 by obouhlel         ###   ########.fr       */
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

int	ft_check_list(t_list *list, t_free *to_free, char *save, t_envi *envp)
{
	if (list == NULL)
	{
		free_all(to_free->newsplit, save);
		free(to_free->not_expend);
		ft_free_envi(envp);
		ft_free_lst(list);
		ft_putendl_fd("exit", STDOUT);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
