/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:39:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 22:39:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	check_next(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (c == '\'')
	{
		while (str[++i])
			if (str[i] == '\'')
				count++;
	}
	else
		while (str[++i])
			if (str[i] == '\"')
				count++;
	return (count);
}

int	check_order_quote(char *str)
{
	int		i;
	bool	open_single;
	bool	open_double;
	int		first;

	open_double = false;
	first = -1;
	open_single = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (first == -1)
				first = 0;
			if (open_single == true)
			{
				if (first == 0 && check_next(&str[i], '\'') == 0
					&& check_next(&str[i], '\"' != 0))
					return (-1);
				else
					open_single = false;
			}
			else
				open_single = true;
		}
		if (str[i] == '\"')
		{
			if (first == -1)
				first = 1;
			if (open_double == true)
			{
				if (first == 1 && check_next(&str[i], '\"') == 0
					&& check_next(&str[i], '\'' != 0))
					return (-1);
				else
					open_double = false;
			}
			else
				open_double = true;
		}
	}
	return (0);
}

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
