/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:26:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 15:41:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// open the files and return the fd
int	ft_open(char *name, t_redir type, int *count_line, t_exec *exec)
{
	if (type == INFILE)
		return (open(name, O_RDONLY));
	else if (type == TRUNC)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (type == HEREDOC)
		return (ft_here_doc(name, count_line, exec));
	return (FAILURE);
}

// split of ft_open_infiles
void	ft_open_init_fd_infile(int *fd, int type)
{
	if (*fd != -2 && *fd != -1 && (type == INFILE || type == HEREDOC))
	{
		ft_close(fd);
	}
}

// open all the infile and return the fd of the last infile
int	ft_open_infiles(t_list *redir, int nb, int *count_line, t_exec *exec)
{
	int		fd;
	int		fd_here_doc;

	fd = -2;
	if (!redir)
		return (fd);
	fd_here_doc = ft_open_infiles_here_doc(redir, count_line, exec);
	while (redir)
	{
		ft_open_init_fd_infile(&fd, redir->type);
		if (redir->type == INFILE)
		{
			fd = ft_open(redir->content, INFILE, count_line, exec);
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

// open all the here_doc and return the fd of the last here_doc
int	ft_open_infiles_here_doc(t_list *redir, int *count_line, t_exec *exec)
{
	int		fd;

	fd = -2;
	while (redir)
	{
		if (fd != -2 && fd != -1 && redir->type == HEREDOC)
		{
			ft_close(&fd);
		}
		if (redir->type == HEREDOC)
		{
			fd = ft_open(redir->content, HEREDOC, count_line, exec);
			if (fd == -1)
				return (FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

// open all the outfile and return the fd of the last outfile
int	ft_open_outfiles(t_list *redir, int *count_line, t_exec *exec)
{
	int	fd;

	fd = -2;
	if (!redir)
		return (fd);
	while (redir)
	{
		if (fd != -2 && fd != -1 && \
			(redir->type == TRUNC || redir->type == APPEND))
			ft_close(&fd);
		if (redir->type == TRUNC)
		{
			fd = ft_open(redir->content, TRUNC, count_line, exec);
			if (fd == -1)
				return (ft_msg(NULL, redir->content, errno, NULL), FAILURE);
		}
		else if (redir->type == APPEND)
		{
			fd = ft_open(redir->content, APPEND, count_line, exec);
			if (fd == -1)
				return (ft_msg(NULL, redir->content, errno, NULL), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}
