/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:05:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:13:46 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	run_heredoc(t_list *lst, t_envi *envi, int *countline, int *exitcode)
{
	t_heredoc	heredoc;
	char		*tmp;
	char		*limiter;
	int			pid;

	heredoc.lst = lst;
	heredoc.envi = envi;
	heredoc.count_line = countline;
	heredoc.exit_code = exitcode;
	while (lst)
	{
		if (lst->type == REDIR && ft_strcmp(lst->content, "<<\0") == 0)
		{
			if (lst->next && lst->next->type == FILES)
			{
				lst = lst->next;
				limiter = ft_strdup(lst->content);
				if (!limiter)
					return (ft_msg_malloc("heredoc.c 1"), FAILURE);
				ft_free((void **)&lst->content);
				tmp = ft_random(10);
				if (!tmp)
					return (ft_msg_malloc("heredoc.c 2"), FAILURE);
				lst->content = ft_strjoin("/tmp/", tmp);
				if (!lst->content)
					return (ft_msg_malloc("heredoc.c 3"), FAILURE);
				ft_free((void **)&tmp);
				pid = fork();
				if (pid == 0)
					ft_heredoc(limiter, lst->content, &heredoc);
				else
				{
					ft_free((void **)&limiter);
					waitpid(pid, NULL, 0);
				}
			}
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_unlink(t_list *lst)
{
	while (lst)
	{
		if (lst->type == REDIR && ft_strcmp(lst->content, "<<\0") == 0)
		{
			if (lst->next)
			{
				lst = lst->next;
				unlink(lst->content);
			}
		}
		if (lst)
			lst = lst->next;
	}
}
