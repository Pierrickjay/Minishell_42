/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:26:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/22 09:42:52 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_open(char *name, t_redir type)
{
	if (type == REDIR_IN)
		return (open(name, O_RDONLY));
	else if (type == REDIR_OUT)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == REDIR_APPEND)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (type == REDIR_HEREDOC)
		return (ft_here_doc(name));
	return (FAILURE);
}

void	ft_open_init_fd_infile(int *fd, int type)
{
	if (*fd != -1 && (type == REDIR_IN || type == REDIR_HEREDOC))
	{
		close(*fd);
		*fd = -1;
	}
}

int	ft_open_infiles(t_list *redir, int infile, int here_doc, int nb)
{
	int		fd;
	int		fd_here_doc;

	fd = -1;
	fd_here_doc = ft_open_infiles_here_doc(redir);
	while (redir)
	{
		ft_open_init_fd_infile(&fd, redir->type);
		if (redir->type == infile)
		{
			fd = ft_open(redir->content, infile);
			if (fd == -1)
				return (FAILURE);
		}
		else if (redir->type == here_doc && --nb == 0)
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
		if (fd != -1 && redir->type == REDIR_HEREDOC)
		{
			close(fd);
			fd = -1;
		}
		if (redir->type == REDIR_HEREDOC)
		{
			fd = ft_open(redir->content, REDIR_HEREDOC);
			if (fd == -1)
				return (FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

int	ft_open_outfiles(t_list *redir, int trunc, int append)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1 && (redir->type == trunc || redir->type == append))
		{
			close(fd);
			fd = -1;
		}
		if (redir->type == trunc)
		{
			fd = ft_open(redir->content, trunc);
			if (fd == -1)
				return (FAILURE);
		}
		else if (redir->type == append)
		{
			fd = ft_open(redir->content, append);
			if (fd == -1)
				return (FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}
