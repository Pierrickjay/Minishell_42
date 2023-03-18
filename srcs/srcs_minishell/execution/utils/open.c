/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:26:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:28:23 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// open the files and return the fd
int	ft_open(char *name, t_redir type)
{
	if (type == INFILE)
		return (open(name, O_RDONLY));
	else if (type == TRUNC)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (FAILURE);
}

// open all the infile and return the fd of the last infile
int	ft_open_infiles(t_shell *shell, t_list *redir)
{
	int		fd;

	fd = -2;
	while (redir)
	{
		if (redir->type == INFILE || redir->type == HEREDOC)
			ft_close(&fd);
		if (redir->type == INFILE)
		{
			fd = ft_open(redir->content, INFILE);
			if (fd == -1)
				return (ft_msg(shell, redir->content, errno, &exit), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

// open all the outfile and return the fd of the last outfile
int	ft_open_outfiles(t_shell *shell, t_list *redir)
{
	int	fd;

	fd = -2;
	while (redir)
	{
		if (redir->type == TRUNC || redir->type == APPEND)
			ft_close(&fd);
		if (redir->type == TRUNC)
		{
			fd = ft_open(redir->content, TRUNC);
			if (fd == -1)
				return (ft_msg(shell, redir->content, errno, &exit), FAILURE);
		}
		else if (redir->type == APPEND)
		{
			fd = ft_open(redir->content, APPEND);
			if (fd == -1)
				return (ft_msg(shell, redir->content, errno, &exit), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}
