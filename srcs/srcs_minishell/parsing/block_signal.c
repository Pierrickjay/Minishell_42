/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:37:45 by pjay              #+#    #+#             */
/*   Updated: 2023/03/09 14:39:41 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	block_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
}

void	unblock_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
}
