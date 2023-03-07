/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:22:31 by pjay              #+#    #+#             */
/*   Updated: 2023/03/07 11:02:29 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	count_lengh(char *str)
{
	int	size;
	int	i;

	i = -1;
	size = (int)ft_strlen(str);
	while (str[++i])
	{
		if (i > 0 && str[i] == '>' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '>'))
		{
			if (str[i + 1] == '>')
				i += 1;
			size += 2;
		}
		else if (i > 0 && str[i] == '<' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '<'))
		{
			if (str[i + 1] == '<')
				i += 1;
			size += 2;
		}
	}
	return (size);
}

char	*finish_it(char *new_str, int i, int j)
{
	new_str[i + j] = '\0';
	new_str = separate_pipe(new_str);
	printf("new_str = %s\n", new_str);
	if (!new_str)
		return (NULL);
	else
		return (new_str);
}

static void	new_string_1(int *i, int *j, char *str, char *new_str)
{
	if (str[*i + 1] && str[*i + 1] == '>')
		*i += fill_string_double(&new_str[*i + *j], &str[*i], '>');
	else
	{
		printf("enter here\n");
		*i += fill_string_single(&new_str[*i + *j], &str[*i], '>');
	}
	*j += 2;
	if (str[*i] != '>')
		new_str[*i + *j] = str[*i];
}

static void	new_string_2(int *i, int *j, char *str, char *new_str)
{
	if (str[*i + 1] && str[*i + 1] == '<')
		*i += fill_string_double(&new_str[*i + *j], &str[*i], '<');
	else
		*i += fill_string_single(&new_str[*i + *j], &str[*i], '<');
	*j += 2;
	if (str[*i] != '<')
		new_str[*i + *j] = str[*i];
}

char	*new_string(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_str = ft_calloc(sizeof(char), (count_lengh(str) + 2));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			i = to_go_next_quote_single(str, new_str, i, j);
		else if (str[i] == '\"')
			i = to_go_next_quote_double(str, new_str, i, j);
		else if (str[i] && str[i] == '>')
			new_string_1(&i, &j, str, new_str);
		else if (str[i] && str[i] == '<')
			new_string_2(&i, &j, str, new_str);
		else
			increment_fill(str, new_str, &i, j);
	}
	return (finish_it(new_str, i, j));
}
