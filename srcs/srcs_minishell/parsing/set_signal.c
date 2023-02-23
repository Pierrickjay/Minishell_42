/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:41:11 by pjay              #+#    #+#             */
/*   Updated: 2023/02/23 10:08:32 by pjay             ###   ########.fr       */
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
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

int	create_siga(void)
{
	struct sigaction	act;

	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handler_end;
	sigaction(SIGINT, &act, NULL);
	return (0);
}
