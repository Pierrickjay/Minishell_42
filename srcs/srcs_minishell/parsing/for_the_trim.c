/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:35:25 by pjay              #+#    #+#             */
/*   Updated: 2023/02/17 10:03:03 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_next_spe(char **split, char **newsplit, int i, int a)
{
	if ((split[i + a][0] == '\'' && split[i + 1 + a]
		&& split[i + 1 + a][0] == '\'')
		|| (split[i + a][0] == '\"'
		&& split[i + 1 + a] && split[i + 1 + a][0] == '\"'))
	{
		newsplit[i] = create_space();
		if (!newsplit[i])
			return (-1);
		return (1);
	}
	return (0);
}

int	deal_w_double(char **newsplit, char **split, int i, int a)
{
	if (split[i + a][1] == '\"')
	{
		newsplit[i] = malloc(sizeof(char));
		if (!newsplit[i])
		{
			printf("out\n");
			return (-1);
		}
		newsplit[i][0] = '\0';
	}
	else
		newsplit[i] = ft_strtrim(split[i + a], "\"");
	return (0);
}

int	deal_w_single(char **newsplit, char **split, int i, int a)
{
	if (split[i + a][1] == '\'')
	{
		newsplit[i] = malloc(sizeof(char));
		if (!newsplit[i])
			return (-1);
		newsplit[i][0] = '\0';
	}
	else
		newsplit[i] = ft_strtrim(split[i + a], "'");
	return (0);
}

int	time_to_trim(char **newsplit, char **split, int i, int a)
{
	bool	enter;

	enter = false;
	if (split[i + a][0] == '\"')
	{
		if (deal_w_double(newsplit, split, i, a) == -1)
			return (-1);
		enter = true;
	}
	if (split[i + a][0] == '\'')
	{
		if (deal_w_double(newsplit, split, i, a) == -1)
			return (-1);
		enter = true;
	}
	if (!enter)
		newsplit[i] = ft_strtrim(split[i + a], "'");
	if (!newsplit[i])
		return (-1);
	return (0);
}

char	**trim_all(char **split)
{
	int		i;
	char	**newsplit;
	int		a;

	a = 0;
	newsplit = malloc(sizeof(char *) * count_split(split) + 1);
	if (!newsplit)
		return (NULL);
	i = -1;
	while (split[++i + a])
	{
		if (!(check_next_spe(split, newsplit, i, a) == 0))
		{
			if (check_next_spe(split, newsplit, i, a) == -1)
				return (NULL);
			a++;
		}
		else
			if (time_to_trim(newsplit, split, i, a) == -1)
				return (NULL);
	}
	newsplit[i] = NULL;
	free_split(split);
	return (newsplit);
}
