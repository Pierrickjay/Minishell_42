/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:41:11 by pjay              #+#    #+#             */
/*   Updated: 2023/02/16 10:50:11 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

extern int	g_sig_int;

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
		block_signal(SIGQUIT);
		return ;
	}
	write(1, "\nminishell>", 11);
	//rl_redisplay();
	block_signal(SIGINT);
	g_sig_int = 1;
	unblock_signal(SIGINT);

}

int	create_siga(void)
{
	struct sigaction	act;

	block_signal(SIGQUIT);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handler_end;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	return (0);
}
