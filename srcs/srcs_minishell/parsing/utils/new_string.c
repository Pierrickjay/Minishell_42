/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:22:31 by pjay              #+#    #+#             */
/*   Updated: 2023/03/06 11:02:57 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	count_lengh(char *str)
{
	int	size;
	int	i;
	// int	tmp;

	i = -1;
	// tmp = 0;
	size = (int)ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '>' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '>'))
		{
			if (str[i + 1] == '>')
				i += 1;
			size += 2;
		}
		else if (str[i] == '<' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '<'))
		{
			if (str[i + 1] == '<')
				i += 1;
			size += 2;
		}
	}
	return (size);
}

char	*new_string(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	i = -1;
	new_str = malloc(sizeof(char) * (count_lengh(str) + 1));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\'')
			i = to_go_next_quote_single(str, new_str, i, j);
		else if (str[i] == '\"')
			i = to_go_next_quote_double(str, new_str, i, j);
		else if (str[i] != ' ' && str[i + 1] && str[i + 1] == '>')
		{
			if (str[i + 2] && str[i + 2] == '>')
				i += fill_string_double(&new_str[i + j], &str[i], '>');
			else
				i += fill_string_single(&new_str[i + j], &str[i], '>');
			j += 2;
		}
		else if (str[i] != ' ' && str[i + 1] && str[i + 1] == '<')
		{
			if (str[i + 2] && str[i + 2] == '<')
				i += fill_string_double(&new_str[i + j], &str[i], '<');
			else
				i += fill_string_single(&new_str[i + j], &str[i], '<');
			j += 2;
		}
		else
			new_str[i + j] = str[i];
	}
	new_str[i + j] = '\0';
	return (new_str);
}
