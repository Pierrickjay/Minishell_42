/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:41:11 by pjay              #+#    #+#             */
/*   Updated: 2023/03/09 19:00:14 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

volatile int	g_check = 0;

void	handler_quit(int signal)
{
	if (signal != SIGQUIT)
	{
		block_signal(SIGQUIT);
		return ;
	}
	printf("Quit (core dumped)");
}

void	handler_end_spe(int signal1)
{
	if (signal1 == SIGINT)
	{
		rl_done = 1;
		g_check = 1;
		write(1, "\n", 1);
		printf("minishell> ");
	}
	else
		return ;
}

void	handler_end(int signal)
{
	if (signal == SIGINT)
	{
		if (g_check == 0)
		{
			block_signal(SIGINT);
			rl_on_new_line();
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
			unblock_signal(SIGINT);
		}
		else
			g_check = 0;
	}
	else
		return ;
}

void	create_siga2(int mode)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	if (mode == PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == HEREDOC)
	{
		act.sa_handler = &handler_end_spe;
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	create_siga(int mode)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	if (mode == MAIN)
	{
		signal(SIGQUIT, SIG_IGN);
		act.sa_handler = &handler_end;
		act.sa_flags = 0;
		sigaction(SIGINT, &act, NULL);
	}
	if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
		create_siga2(mode);
	return (0);
}
