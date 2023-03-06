/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:35:25 by pjay              #+#    #+#             */
/*   Updated: 2023/03/04 23:06:05 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	go_next_quote(char *str, int index, char c)
{
	int	i;

	i = 0;
	if (c == '\'')
	{
		while (str[++i])
		{
			if (i <= index)
				continue ;
			if (str[i] == '\'')
				return (i);
		}
	}
	else
	{
		while (str[++i])
		{
			if (i <= index)
				continue ;
			if (str[i] == '\"')
				return (i);
		}
	}
	return (i);
}

// le malloc de strdup n'est pas check car si ca a
// return null alors ca rentrera pas dans le while
// et ca returnera new_one qui vaut null

char	*make_it_clean(char *str)
{
	int				i;
	char			*new_one;
	int				tmp;

	i = -1;
	new_one = ft_strdup_modif(str, 0);
	while (new_one[++i] && (size_t)i < ft_strlen(new_one))
	{
		if (new_one[i] == '\'')
		{
			tmp = i;
			i = go_next_quote(new_one, i, '\'') - 2;
			new_one = ft_strdup_modif(remove_single(new_one, tmp), 1);
		}
		else if (new_one[i] == '\"')
		{
			tmp = i;
			i = go_next_quote(new_one, i, '\"') - 2;
			new_one = ft_strdup_modif(remove_double(new_one, tmp), 1);
		}
		if (!new_one)
			return (NULL);
	}
	return (new_one);
}

char	**trim_all(char **split)
{
	int		i;
	char	**newsplit;
	int		a;

	a = 0;
	newsplit = malloc(sizeof(char *) * (count_split(split) + 1));
	if (!newsplit)
		return (NULL);
	i = -1;
	while (split[++i + a])
	{
		newsplit[i] = make_it_clean(split[i + a]);
		if (!newsplit[i])
			return (NULL);
		if (count_quote_single(newsplit[i]) == -1)
			return (free_inverse_split(split, count_split(split)));
	}
	newsplit[i++] = NULL;
	free_split(split);
	return (newsplit);
}
