/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/14 14:02:54 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	*create_space(void)
{
	char	*newsplit;

	newsplit = malloc(sizeof(char) * 2);
	if (!newsplit)
		return (NULL);
	newsplit[0] = ' ';
	newsplit[1] = '\0';
	return (newsplit);
}
