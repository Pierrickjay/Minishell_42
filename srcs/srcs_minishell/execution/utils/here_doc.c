/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:13:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 13:04:26 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

extern int	count_line;
extern sig_atomic_t g_test;

void	to_print_error(char *end)
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(count_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(end, 2);
	ft_putendl_fd("')", 2);
}

// get the heredoc from the user
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
	create_siga(HEREDOC);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
		{
			if (g_test == 0)
				to_print_error(end);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			return (free(limiter), free(line), close(fd[1]), fd[0]);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	g_test = 0;
	free(limiter);
	close(fd[1]);
	return (fd[0]);
}
