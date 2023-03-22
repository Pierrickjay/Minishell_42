/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/22 10:14:43 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// free the child process variables
void	ft_free_child(t_shell *shell, char **path, char *cmd)
{
	if (shell)
		ft_free_shell(shell);
	if (path)
		ft_free_strs(path);
	if (cmd)
		free(cmd);
}

// free one element of the list of envi and initialize it to NULL
void	ft_free_envi_delone(t_envi *envi)
{
	ft_free((void **)&envi->key);
	ft_free((void **)&envi->value);
	ft_free((void **)&envi);
}

void	ft_free_lst_delone(t_list **lst, t_list *previous)
{
	t_list	*next;

	next = (*lst)->next;
	ft_lst_print_type(next);
	ft_free((void **)&(*lst)->content);
	ft_free((void **)lst);
	(*lst) = previous;
	if (next)
		(*lst)->next = next;
	else
		(*lst)->next = NULL;
}

// free the heredoc structure
void	ft_free_heredoc(t_heredoc *heredoc, char *limiter, char *line, int fd)
{
	if (heredoc->lst)
		ft_free_lst(heredoc->lst);
	if (heredoc->envi)
		ft_free_envi(heredoc->envi);
	if (limiter)
		ft_free((void **)&limiter);
	if (line)
		ft_free((void **)&line);
	ft_close(&fd);
}
