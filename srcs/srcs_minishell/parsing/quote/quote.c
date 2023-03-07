/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:45:58 by pjay              #+#    #+#             */
/*   Updated: 2023/03/07 10:21:13 by pjay             ###   ########.fr       */
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
	ft_free((void **)&str);
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
