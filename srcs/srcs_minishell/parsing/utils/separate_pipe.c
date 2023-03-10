/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:10:09 by pjay              #+#    #+#             */
/*   Updated: 2023/03/10 12:24:41 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	count_lengh_pipe(char *str)
{
	int	i;
	int	count;

	if (str && str[0])
		count = ft_strlen(str);
	else
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			count += 2;
			while (str[i] == '|')
				i++;
		}
		else
			i++;
	}
	return (count + i);
}

void	fill_new_string(char *new_str, int *i, int *j, char *str)
{
	new_str[*i + *j] = str[*i];
	(*j)++;
	new_str[*i + *j] = ' ';
	(*i)++;
	while (str[*i] && str[*i] == '|')
	{
		new_str[*i + *j] = str[*i];
		(*i)++;
	}
	new_str[*i + *j] = ' ';
	(*j)++;
	new_str[*i + *j] = str[*i];
}

char	*separate_pipe(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	i = -1;
	new_str = malloc(sizeof(char) * (count_lengh_pipe(str) + 2));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	while (str[++i])
	{
		if (str[i] == '\'')
			i = to_go_next_quote_single(str, new_str, i, j);
		if (str[i] == '\"')
			i = to_go_next_quote_double(str, new_str, i, j);
		else if (str[i] != ' ' && str[i + 1] && str[i + 1] == '|')
			fill_new_string(new_str, &i, &j, str);
		else
			new_str[i + j] = str[i];
	}
	new_str[i + j] = '\0';
	return (free(str), new_str);
}
