/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:26:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 11:57:51 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_here_doc(char *end)
{
	static char	*line = "START";
	char		*limiter;
	int			fd[2];

	limiter = ft_strjoin(end, "\n");
	if (!limiter)
		return (-1);
	if (pipe(fd) == -1)
		return (free(limiter), -1);
	while (1)
	{
		if (line)
			ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			return (free(limiter), free(line), close(fd[1]), fd[0]);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	free(limiter);
	close(fd[1]);
	return (fd[0]);
}

int	ft_open(char *name, int type)
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

int	ft_open_infiles(t_list *redir, int infile, int here_doc)
{
	int	fd;

	fd = -1;
	while (redir)
	{
		if (fd != -1)
			close(fd);
		if (redir->type != -1)
		{
			if (redir->type == infile)
			{
				fd = ft_open(redir->content, infile);
				if (fd == -1)
					return (FAILURE);
			}
			else if (redir->type == here_doc)
			{
				fd = ft_open(redir->content, here_doc);
				if (fd == -1)
					return (FAILURE);
			}
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
		if (fd != -1)
			close(fd);
		if (redir->type != -1)
		{
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
		}
		redir = redir->next;
	}
	return (fd);
}

void	ft_close_pipes(int **pipes, size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
