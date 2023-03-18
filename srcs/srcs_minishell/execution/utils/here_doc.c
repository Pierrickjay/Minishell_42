/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:13:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 12:00:39 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/parsing.h"

extern volatile int	g_check;

// get the heredoc from the user
int	ft_here_doc(t_exec *exec, char *end)
{
	char		*line;
	int			fd[2];

	line = NULL;
	create_siga(HEREDOC);
	if (pipe(fd) == -1)
		return (-1);
	while (!g_check)
	{
		line = ft_get_line(exec, end, fd);
		if (!line)
			return (ft_close(&fd[0]), ft_close(&fd[1]), FAILURE);
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
			return (free(line), ft_close(&fd[1]), fd[0]);
		ft_putendl_fd(line, fd[1]);
		ft_free((void **)&line);
	}
	if (g_check == 1)
		finish_here_doc(exec, fd, line);
	return (free(line), ft_close (&fd[1]), fd[0]);
}

char	*ft_get_line(t_exec *exec, char *end, int fd[2])
{
	char	*line;

	line = readline("> ");
	(exec->count_line[0])++;
	if (!line || g_check == 1)
	{
		if (!g_check)
			to_print_error(exec, end, exec->count_line, fd);
		finish_here_doc(exec, fd, line);
	}
	line = ft_update_str_var(exec->envi, line, exec->exit_code[0]);
	if (!line)
		return (ft_close(&fd[1]), ft_close(&fd[0]), NULL);
	return (line);
}

void	finish_here_doc(t_exec *exec, int fd[2], char *line)
{
	free(line);
	ft_close (&fd[1]);
	ft_close(&fd[0]);
	ft_free_exec(exec);
	exit(130);
}

void	to_print_error(t_exec *exec, char *end, int *count_line, int fd[2])
{
	if (g_check == 1)
	{
		ft_free_exec(exec);
		ft_close(&fd[0]);
		ft_close(&fd[1]);
		g_check = 0;
		exit(2);
	}
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(*count_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(end, 2);
	ft_putendl_fd("')", 2);
}
