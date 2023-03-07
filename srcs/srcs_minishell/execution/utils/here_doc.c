/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:13:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 15:25:59 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

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
	create_siga(MAIN);
	while (1)
	{
		if (line)
			ft_putstr_fd("> ", 1);
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
