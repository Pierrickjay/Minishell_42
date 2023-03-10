/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:52:55 by pjay              #+#    #+#             */
/*   Updated: 2023/03/10 15:51:59 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	check_single_quote(char *str, bool *open_single, bool *open_double, int *i)
{
	if (*open_single == true)
		*open_single = false;
	else
		*open_single = true;
	while (str[*i] && str[*i] != '\'')
	{
		if (str[*i] == '\"')
		{
			if (*open_double == true)
				*open_double = false;
			else
				*open_double = true;
		}
		(*i)++;
	}
	if (!str[*i] && (*open_single == true || *open_single == true))
		return (-1);
	else
	{
		if (*open_single == false)
			*open_single = true;
		else
			*open_single = false;
	}
	return (0);
}

int	check_double_quote(char *str, bool *open_single, bool *open_double, int *i)
{
	if (*open_double == false)
				*open_double = true;
	else
		*open_double = false;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '\'')
		{
			if (*open_single == true)
				*open_double = false;
			else
				*open_single = true;
		}
		(*i)++;
	}
	if (!str[*i] && (*open_single == true || *open_single == true))
		return (-1);
	else
	{
		if (*open_single == false)
			*open_single = true;
		else
			*open_single = false;
	}
	return (0);
}

int	check_if_open(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (-1);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (-1);
		}
	}
	return (0);
}

int	count_quote_single(char *str)
{
	int		i;
	bool	open_single;
	bool	open_double;

	open_single = false;
	open_double = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			if (check_single_quote(str, &open_single, &open_double, &i) == -1)
				return (-1);
		if (str[i] == '\"')
			if (check_double_quote(str, &open_single, &open_double, &i) == -1)
				return (-1);
	}
	if (check_if_open(str) == -1)
		return (-1);
	return (0);
}
