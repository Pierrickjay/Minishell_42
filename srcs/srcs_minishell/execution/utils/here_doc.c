/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:13:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 07:21:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	to_print_error(char *end, int *count_line, t_exec *exec, int fd[2])
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(*count_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(end, 2);
	ft_putendl_fd("')", 2);
	// global ici pour savoir si ctrl c ou ctrl d 
	// pour ctrl c
	ft_free_exec(exec);
	ft_close(&fd[0]);
	ft_close(&fd[1]);
	exit(2);
}

// get the heredoc from the user
int	ft_here_doc(char *end, int *count_line, t_exec *exec)
{
	char		*line;
	int			fd[2];

	create_siga(HEREDOC);
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		(*count_line)++;
		if (!line)
			to_print_error(end, count_line, exec, fd);
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
			return (free(line), ft_close(&fd[1]), fd[0]);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	ft_close (&fd[1]);
	return (fd[0]);
}
