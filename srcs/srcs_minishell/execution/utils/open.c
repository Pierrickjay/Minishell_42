/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:26:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 11:53:35 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// open the files and return the fd
int	ft_open(t_exec *exec, char *name, t_redir type)
{
	if (type == INFILE)
		return (open(name, O_RDONLY));
	else if (type == TRUNC)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (type == APPEND)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (type == HEREDOC)
		return (ft_here_doc(exec, name));
	return (FAILURE);
}

// open all the infile and return the fd of the last infile
int	ft_open_infiles(t_exec *exec, t_list *redir, int nb)
{
	int		fd;
	int		fd_here_doc;

	fd = -2;
	fd_here_doc = ft_open_infiles_here_doc(exec, redir);
	while (redir)
	{
		if (redir->type == INFILE || redir->type == HEREDOC)
			ft_close(&fd);
		if (redir->type == INFILE)
		{
			fd = ft_open(exec, redir->content, INFILE);
			if (fd == -1)
				return (ft_msg(exec, redir->content, errno, &exit), FAILURE);
		}
		else if (redir->type == HEREDOC && --nb == 0)
		{
			fd = fd_here_doc;
			if (fd == -1)
				return (ft_msg(exec, NULL, errno, &exit), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

// open all the here_doc and return the fd of the last here_doc
int	ft_open_infiles_here_doc(t_exec *exec, t_list *redir)
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
			fd = ft_open(exec, redir->content, HEREDOC);
			if (fd == -1)
				return (FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}

// open all the outfile and return the fd of the last outfile
int	ft_open_outfiles(t_exec *exec, t_list *redir)
{
	int	fd;

	fd = -2;
	while (redir)
	{
		if (redir->type == TRUNC || redir->type == APPEND)
			ft_close(&fd);
		if (redir->type == TRUNC)
		{
			fd = ft_open(exec, redir->content, TRUNC);
			if (fd == -1)
				return (ft_msg(exec, redir->content, errno, &exit), FAILURE);
		}
		else if (redir->type == APPEND)
		{
			fd = ft_open(exec, redir->content, APPEND);
			if (fd == -1)
				return (ft_msg(exec, redir->content, errno, &exit), FAILURE);
		}
		redir = redir->next;
	}
	return (fd);
}
