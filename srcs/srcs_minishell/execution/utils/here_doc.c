/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:13:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 15:21:10 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

extern sig_atomic_t	g_check;

void	to_print_error(char *end, int *count_line, t_exec *exec, int fd[2])
{
	if (g_check == 1)
	{
		printf("enter here\n");
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

// get the heredoc from the user
int	ft_here_doc(char *end, int *count_line, t_exec *exec)
{
	char		*line;
	int			fd[2];

	create_siga(HEREDOC);
	if (pipe(fd) == -1)
		return (-1);
	printf("pid = %d\n", *exec->pid);
	while (1)
	{
		if (g_check == 1)
			exit (0);
		line = readline("> ");
		(*count_line)++;
		if (!line || g_check == 1)
		{
			if (!g_check)
				to_print_error(end, count_line, exec, fd);
			break ;
		}
		add_history(line);
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
			return (free(line), ft_close(&fd[1]), fd[0]);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	return (ft_close (&fd[1]), fd[0]);
}
