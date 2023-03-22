/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:41:44 by pjay              #+#    #+#             */
/*   Updated: 2023/03/22 10:25:16 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	count_lengh_quote(char *str)
{
	int	size;
	int	i;

	i = -1;
	size = (int)ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[i] && str[i] == '\'')
				i++;
			size += 2;
		}
		if (str[i] == '\"')
		{
			while (str[i] && str[i] == '\"')
				i++;
			size += 2;
		}
		if (!str[i])
			return (size + i);
	}
	return (size + i);
}

void	increment_fill_quote(char *str, char *new_str, int *i, int j)
{
	new_str[*i + j] = str[*i];
	(*i)++;
}

void	fill_quote_single_space(char *str, char *new_str, int *i, int *j)
{
	*i = to_go_next_quote_single(str, new_str, *i, *j) + 1;
	if (str[*i] && str[*i] != ' ')
	{
		new_str[*i + *j] = -2;
		(*j)++;
	}
	new_str[*i + *j] = ' ';
	(*j)++;
}

void	fill_quote_double_space(char *str, char *new_str, int *i, int *j)
{
	*i = to_go_next_quote_double(str, new_str, *i, *j) + 1;
	if (str[*i] && str[*i] != ' ')
	{
		new_str[*i + *j] = -2;
		(*j)++;
	}
	new_str[*i + *j] = ' ';
	(*j)++;
}

char	*new_string_quote(char *str)
{
	char		*new_str;
	int			i;
	int			j;
	const int	size = ft_strlen(str);

	j = 0;
	i = 0;
	new_str = ft_calloc(sizeof(char), (count_lengh_quote(str) + 2));
	if (!new_str)
		return (NULL);
	while (i <= size)
	{
		if (str[i] == '$' && str[i + 1]
			&& (str[i + 1] == '\'' || str[i + 1] == '\"') && i++)
				j--;
		if (str[i] == '\'')
			fill_quote_single_space(str, new_str, &i, &j);
		else if (str[i] == '\"')
			fill_quote_double_space(str, new_str, &i, &j);
		else
			increment_fill_quote(str, new_str, &i, j);
	}
	free(str);
	return (new_str);
}
