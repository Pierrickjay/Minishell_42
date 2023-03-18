/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:05:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 18:02:07 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

extern volatile int	g_check;

int	ft_run_heredoc(t_list *lst, t_envi *envi, int *count_line, int *exit_code)
{
	t_heredoc	heredoc;
	char		*tmp;
	char		*limiter;
	int			pid;

	heredoc.lst = lst;
	heredoc.envi = envi;
	heredoc.count_line = count_line;
	heredoc.exit_code = exit_code;
	while (lst)
	{
		if (lst->type == REDIR && ft_strcmp(lst->content, "<<\0") == 0)
		{
			if (lst->next && lst->next->type == FILES)
			{
				lst = lst->next;
				limiter = ft_strdup(lst->content);
				if (!limiter)
					return (ft_msg_malloc("heredoc.c 1"), FAILURE);
				ft_free((void **)&lst->content);
				tmp = ft_random(10);
				if (!tmp)
					return (ft_msg_malloc("heredoc.c 2"), FAILURE);
				lst->content = ft_strjoin("/tmp/", tmp);
				if (!lst->content)
					return (ft_msg_malloc("heredoc.c 3"), FAILURE);
				ft_free((void **)&tmp);
				pid = fork();
				if (pid == 0)
					ft_heredoc(limiter, lst->content, &heredoc);
				else
				{
					ft_free((void **)&limiter);
					waitpid(pid, NULL, 0);
				}
			}
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_heredoc(char *limiter, char *name_file, t_heredoc *heredoc)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(name_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_msg_heredoc(heredoc, "open heredoc", errno, &exit));
	create_siga(HEREDOC);
	while (!g_check)
	{
		line = readline("> ");
		(heredoc->count_line[0])++;
		if (!line || g_check == 1)
		{
			if (!g_check)
				to_print_error(heredoc, limiter, fd);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			return (free(line), free(limiter), ft_free_heredoc(heredoc), ft_close(&fd), exit(0));
		tmp = line;
		line = ft_expend(heredoc->envi, tmp, heredoc->exit_code[0]);
		if (!line)
			return (ft_msg_heredoc(heredoc, "malloc", errno, &exit));
		ft_putendl_fd(line, fd);
		ft_free((void **)&line);
	}
	if (g_check == 1)
		finish_here_doc(fd, limiter, line, heredoc);
	return (ft_free_heredoc(heredoc), ft_close(&fd), exit(0));
}

void	finish_here_doc(int fd, char *limiter, char *line, t_heredoc *heredoc)
{
	ft_free((void **)&limiter);
	ft_free((void **)&line);
	ft_close(&fd);
	ft_free_heredoc(heredoc);
	exit(130);
}

void	to_print_error(t_heredoc *heredoc, char *limiter, int fd)
{
	if (g_check == 1)
	{
		ft_close(&fd);
		ft_free((void **)&limiter);
		ft_free_heredoc(heredoc);
		g_check = 0;
		exit(2);
	}
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(heredoc->count_line[0], 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}

void	ft_msg_heredoc(t_heredoc *heredoc, char *str, int value, void (*f)(int))
{
	if (value > 0 && str)
		perror(str);
	else if (value > 0)
		ft_putendl_fd(strerror(errno), STDERR);
	if (!f && heredoc)
		ft_free_heredoc(heredoc);
	if (f)
	{
		if (heredoc)
			ft_free_heredoc(heredoc);
		f(value);
	}
}

void	ft_unlink(t_list *lst)
{
	while (lst)
	{
		if (lst->type == REDIR && ft_strcmp(lst->content, "<<\0") == 0)
		{
			if (lst->next)
			{
				lst = lst->next;
				unlink(lst->content);
			}
		}
		if (lst)
			lst = lst->next;
	}
}
