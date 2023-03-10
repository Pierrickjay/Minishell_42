/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:58:59 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 17:33:08 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// free a pointer of pointer and initialize it to NULL
void	ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		ft_free((void **)&strs[i]);
		i++;
	}
	ft_free((void **)&strs);
}

// free the list andd initialize it to NULL
void	ft_free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_free((void **)&lst->content);
		ft_free((void **)&lst);
		lst = tmp;
	}
}

// free the pipes array and initialize it to NULL
void	ft_free_pipes(int **pipes, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_free((void **)&pipes[i]);
		i++;
	}
	ft_free((void **)&pipes);
}

void	ft_free_nb_redir_type(int **nb_redir_type, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		ft_free((void **)&nb_redir_type[i]);
		i++;
	}
	ft_free((void **)&nb_redir_type);
}

// free the args array and initialize it to NULL
void	ft_free_args(char ***args, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_free_strs(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}
