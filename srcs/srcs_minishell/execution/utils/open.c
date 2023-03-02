/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:26:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 12:32:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_open(char *name, t_redir type)
{
	if (type == INFILE)
		return (open(name, O_RDONLY));
	else if (type == TRUNC)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (type == HEREDOC)
		return (ft_here_doc(name));
	return (FAILURE);
}

void	ft_open_init_fd_infile(int *fd, int type)
{
	if (*fd != -1 && (type == INFILE || type == HEREDOC))
	{
		close(*fd);
		*fd = -1;
	}
}

int	ft_open_infiles(t_list *redir, int nb)
{
	int		fd;
	int		fd_here_doc;

	fd = -1;
	fd_here_doc = ft_open_infiles_here_doc(redir);
	while (redir)
	{
		ft_open_init_fd_infile(&fd, redir->type);
		if (redir->type == INFILE)
		{
			fd = ft_open(redir->content, INFILE);
			if (fd == -1)
				return (ft_msg(NULL, redir->content, errno, NULL), FAILURE);
		}
		else if (redir->type == HEREDOC && --nb == 0)
		{
			fd = fd_here_doc;
			if (fd == -1)
				return (FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

int	ft_open_infiles_here_doc(t_list *redir)
{
	int		fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1 && redir->type == HEREDOC)
		{
			close(fd);
			fd = -1;
		}
		if (redir->type == HEREDOC)
		{
			fd = ft_open(redir->content, HEREDOC);
			if (fd == -1)
				return (FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

int	ft_open_outfiles(t_list *redir)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1 && (redir->type == TRUNC || redir->type == APPEND))
		{
			close(fd);
			fd = -1;
		}
		if (redir->type == TRUNC)
		{
			fd = ft_open(redir->content, TRUNC);
			if (fd == -1)
				return (ft_msg(NULL, redir->content, errno, NULL), FAILURE);
		}
		else if (redir->type == APPEND)
		{
			fd = ft_open(redir->content, APPEND);
			if (fd == -1)
				return (ft_msg(NULL, redir->content, errno, NULL), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}
