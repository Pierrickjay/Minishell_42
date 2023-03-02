/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:59:46 by pjay              #+#    #+#             */
/*   Updated: 2023/03/01 13:12:57 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

size_t	split_w_single(const char *s)
{
	size_t	i;

	i = 1;
	while (s[i + 1] && s[i] != '\'')
		i++;
	i++;
	return (i);
}

size_t	split_w_double(const char *s)
{
	size_t	i;

	i = 1;
	while (s[i + 1] && s[i] != '\"')
		i++;
	i++;
	return (i);
}

int	count_word(const char *s, bool single)
{
	size_t	count;

	if (single == true)
	{
		count = split_w_single(s);
		count--;
		return (count);
	}
	else
	{
		count = split_w_double(s);
		count--;
		return (count);
	}
}
