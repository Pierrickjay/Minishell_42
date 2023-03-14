/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 06:56:24 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/14 07:06:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// create a new heredoc element
t_hdoc	*ft_heredoc_new(char *limiter, int fd, int id)
{
	t_hdoc	*new;

	new = (t_hdoc *)malloc(sizeof(t_hdoc));
	if (!new)
		return (NULL);
	new->limiter = limiter;
	new->fd = fd;
	new->id = id;
	new->next = NULL;
	return (new);
}
