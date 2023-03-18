/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:05:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 20:18:00 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	run_heredoc(t_list *lst, t_envi *envi, int *countline, int *exitcode)
{
	t_heredoc	heredoc;

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
				if (run_heredoc_bis(&heredoc, lst))
					return (EXIT_FAILURE);
			}
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

int	run_heredoc_bis(t_heredoc *heredoc, t_list *lst)
{
	char	*tmp;
	char	*limiter;
	int		pid;

	limiter = ft_strdup(lst->content);
	if (!limiter)
		return (ft_msg_malloc("heredoc_1.c (47)"), EXIT_FAILURE);
	ft_free((void **)&lst->content);
	tmp = ft_random(10);
	if (!tmp)
		return (free(limiter), ft_msg_malloc("heredoc_1.c (51)"), EXIT_FAILURE);
	lst->content = ft_strjoin("/tmp/", tmp);
	if (!lst->content)
		return (free(tmp), free(limiter), ft_msg_malloc("heredoc_1.c (54)"), 1);
	ft_free((void **)&tmp);
	pid = fork();
	if (pid == -1)
		return (free(tmp), free(limiter), perror("pipe heredoc"), 1);
	if (pid == 0)
		ft_heredoc(limiter, lst->content, heredoc);
	else
		waitpid(pid, NULL, 0);
	return (ft_free((void **)&limiter), EXIT_SUCCESS);
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
