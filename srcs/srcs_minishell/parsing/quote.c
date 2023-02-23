/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:45:58 by pjay              #+#    #+#             */
/*   Updated: 2023/02/23 14:20:24 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'')
				count_s++;
			if (str[i][j] == '\"')
				count_d++;
			j++;
		}
	}
	if (count_s % 2 != 0)
		return (-1);
	if (count_d % 2 != 0)
		return (-1);
	return (0);
}

char	*remove_single(char *str)
{
	char	*new_one;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_one = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (new_one == NULL)
		return (NULL);
	while (str[i + j])
	{
		if (str[i + j] == '\'')
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

char	*remove_double(char *str)
{
	char	*new_one;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_one = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (new_one == NULL)
		return (NULL);
	while (str[i + j])
	{
		if (str[i + j] == '\"')
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

int	quote_left(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

char	*make_it_clean(char *str)
{
	int		i;
	char	*new_one;

	i = 0;
	new_one = ft_strdup_modif(str, 0);
	if (!new_one)
		return (NULL);
	while (quote_left(new_one) != 0)
	{
		if (str[i] == '\'')
			new_one = ft_strdup_modif(remove_single(new_one), 1);
		if (str[i] == '\"')
			new_one = ft_strdup_modif(remove_double(new_one), 1);
		if (!new_one)
			return (NULL);
		i++;
		if (i == (int)ft_strlen(str) - 1)
			i = 0;
	}
	return (new_one);
}
