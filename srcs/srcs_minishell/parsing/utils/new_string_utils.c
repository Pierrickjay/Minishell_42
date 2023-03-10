/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:16:06 by pjay              #+#    #+#             */
/*   Updated: 2023/03/09 14:20:18 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	to_go_next_quote_single(char *str, char *new_str, int i, int j)
{
	int	tmp;

	tmp = i;
	while (i <= go_next_quote(str, tmp, '\''))
	{
		new_str[i + j] = str[i];
		i++;
	}
	i--;
	return (i);
}

int	to_go_next_quote_double(char *str, char *new_str, int i, int j)
{
	int	tmp;

	tmp = i;
	while (i <= go_next_quote(str, tmp, '\"'))
	{
		new_str[i + j] = str[i];
		i++;
	}
	i--;
	return (i);
}

int	fill_string_double(char *new_str, char *str, char c)
{
	if (c == '>')
	{
		new_str[0] = ' ';
		new_str[1] = str[0];
		new_str[2] = '>';
		new_str[3] = ' ';
	}
	else
	{
		new_str[0] = ' ';
		new_str[1] = str[0];
		new_str[2] = '<';
		new_str[3] = ' ';
	}
	return (2);
}

int	fill_string_single(char *new_str, char *str, char c)
{
	if (c == '>')
	{
		new_str[0] = ' ';
		new_str[1] = str[0];
		new_str[2] = ' ';
	}
	if (c == '<')
	{
		new_str[0] = ' ';
		new_str[1] = str[0];
		new_str[2] = ' ';
	}
	return (1);
}

void	increment_fill(char *str, char *new_str, int *i, int j)
{
	new_str[*i + j] = str[*i];
	(*i)++;
}
