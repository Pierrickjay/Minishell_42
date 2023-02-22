/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:45:58 by pjay              #+#    #+#             */
/*   Updated: 2023/02/22 15:51:42 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'')
				count_s++;
			if (str[i][j] == '\"')
				count_d++;
			j++;
		}
	}
	if (count_s % 2 != 0)
		return (-1);
	if (count_d % 2 != 0)
		return (-1);
	return (0);
}
