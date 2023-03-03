/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:52:55 by pjay              #+#    #+#             */
/*   Updated: 2023/03/03 12:40:05 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	count_quote(char **str)
{
	int	count_s;
	int	count_d;
	int	i;
	int	j;

	count_d = 0;
	count_s = 0;
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '\'')
				count_s++;
			if (str[i][j] == '\"')
				count_d++;
		}
	}
	if (count_s % 2 != 0)
		return (-1);
	if (count_d % 2 != 0)
		return (-1);
	return (0);
}

int	count_quote_single(char *str)
{
	int	count_s;
	int	count_d;
	int	i;

	count_d = 0;
	count_s = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			count_s++;
		if (str[i] == '\"')
			count_d++;
	}
	if (count_s % 2 != 0)
		return (-1);
	if (count_d % 2 != 0)
		return (-1);
	return (0);
}
