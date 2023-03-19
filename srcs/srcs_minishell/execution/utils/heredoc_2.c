/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:59:48 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:35:05 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

extern volatile int	g_check;

// open the file and run the heredoc
void	ft_heredoc(char *limiter, char *name_file, t_heredoc *heredoc)
{
	int		fd;
	char	*line;

	fd = open(name_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_msg_heredoc(heredoc, "open heredoc", errno, &exit));
	create_siga(HEREDOC);
	while (!g_check)
	{
		line = ft_get_line(heredoc, limiter, fd);
		if (!line || g_check == 1)
		{
			if (!g_check)
				to_print_error(heredoc, limiter, fd);
			break ;
		}
		ft_putendl_fd(line, fd);
		ft_free((void **)&line);
	}
	if (g_check == 1)
		finish_here_doc(fd, limiter, line, heredoc);
	return (ft_free_heredoc(heredoc, limiter, NULL, fd), exit(0));
}

// get the line and check if it's the limiter
char	*ft_get_line(t_heredoc *heredoc, char *limiter, int fd)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	(heredoc->count_line[0])++;
	if (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			return (ft_free_heredoc(heredoc, limiter, line, fd), exit(0), NULL);
		tmp = line;
		line = ft_expend(heredoc->envi, tmp, heredoc->exit_code[0]);
		if (!line)
			return (ft_msg_heredoc(heredoc, "malloc", errno, &exit), NULL);
	}
	return (line);
}

// when Ctrl + C is pressed
void	finish_here_doc(int fd, char *limiter, char *line, t_heredoc *heredoc)
{
	ft_free_heredoc(heredoc, limiter, line, fd);
	exit(130);
}

// when Ctrl + D is pressed
void	to_print_error(t_heredoc *heredoc, char *limiter, int fd)
{
	if (g_check == 1)
	{
		ft_free_heredoc(heredoc, limiter, NULL, fd);
		g_check = 0;
		exit(2);
	}
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(heredoc->count_line[0], 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}

// print the error message
void	ft_msg_heredoc(t_heredoc *heredoc, char *str, int n, void (*f)(int))
{
	if (n > 0 && str)
		perror(str);
	else if (n > 0)
		ft_putendl_fd(strerror(errno), STDERR);
	if (!f && heredoc)
		ft_free_heredoc(heredoc, NULL, NULL, -1);
	if (f)
	{
		if (heredoc)
			ft_free_heredoc(heredoc, NULL, NULL, -1);
		f(n);
	}
}
