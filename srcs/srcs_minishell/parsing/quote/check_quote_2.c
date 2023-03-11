/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:16:17 by pjay              #+#    #+#             */
/*   Updated: 2023/03/11 09:59:57 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	check_if_expend(char *old_str)
{
	int	i;

	i = -1;
	while (old_str[++i])
	{
		if (old_str[i] == '\'')
		{
			while (old_str[++i] && old_str[i] != '\'')
			{
				if (old_str[i] == '\"')
					break ;
				if (old_str[i] == '$')
					return (1);
			}
			if (!old_str[i])
				return (0);
		}
	}
	return (0);
}

int	check_if_in_quote(char *old_str)
{
	int	i;

	i = -1;
	while (old_str[++i])
	{
		if (old_str[i] == '\'')
		{
			i++;
			while (old_str[i] && old_str[i] != '\'')
				i++;
			if (old_str[i])
				return (1);
		}
		if (old_str[i] == '\"')
		{
			i++;
			while (old_str[i] && old_str[i] != '\"')
				i++;
			if (old_str[i])
				return (1);
		}
	}
	return (0);
}
