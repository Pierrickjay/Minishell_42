/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:45:58 by pjay              #+#    #+#             */
/*   Updated: 2023/03/04 23:05:30 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	*remove_single(char *str, int index)
{
	char	*new_one;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new_one = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (new_one == NULL)
		return (NULL);
	while (str[++i] && i < index)
		new_one[i] = str[i];
	while (str[i + j])
	{
		if (str[i + j] == '\'' && j != 2)
			j++;
		else
		{
			new_one[i] = str[i + j];
			i++;
		}
	}
	new_one[i] = '\0';
	free(str);
	return (new_one);
}

char	*remove_double(char *str, int index)
{
	char	*new_one;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new_one = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (new_one == NULL)
		return (NULL);
	while (str[++i] && i < index)
		new_one[i] = str[i];
	while (str[i + j])
	{
		if (str[i + j] == '\"' && j != 2)
			j++;
		else
		{
			new_one[i] = str[i + j];
			i++;
		}
	}
	new_one[i] = '\0';
	free(str);
	return (new_one);
}
