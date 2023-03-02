/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:41:11 by pjay              #+#    #+#             */
/*   Updated: 2023/03/02 14:56:48 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

sig_atomic_t	g_check = 0;

void	block_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
}

void	unblock_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
}

void	handler_end(int signal)
{
	if (signal != SIGINT)
	{
		block_signal(SIGINT);
		return ;
	}
	if (g_check == 0)
	{
		block_signal(SIGINT);
		//printf("test\n");
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		//printf("\ng_check = %d\n", g_check);
		rl_redisplay();
		unblock_signal(SIGINT);
	}
	else if(g_check == 1)
	{
		printf("enter here when g_chech = 1\n");
		write(1, "\n", 1);
	}
	else
	{
		printf("enter here when g_chech > 1\n");
		return ;
	}

}

int	create_siga(int mode)
{
	struct sigaction	act;

	if (mode == MAIN)
	{
		signal(SIGQUIT, SIG_IGN);
		ft_bzero(&act, sizeof(act));
		act.sa_handler = &handler_end;
		sigaction(SIGINT, &act, NULL);
	}
	if (mode == CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	if (mode == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	return (0);
}
