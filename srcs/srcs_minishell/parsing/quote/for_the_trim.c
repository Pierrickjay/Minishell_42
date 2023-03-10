/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:35:25 by pjay              #+#    #+#             */
/*   Updated: 2023/03/10 08:43:31 by pjay             ###   ########.fr       */
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

char	*make_it_clean(char *str, int tmp)
{
	int				i;
	char			*new_one;

	i = -1;
	new_one = ft_strdup_modif(str, 0);
	if (!new_one)
		return (NULL);
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

int	trim_all_2(char **split, t_free *to_free)
{
	to_free->newsplit = malloc(sizeof(char *) * (count_split(split) + 1));
	if (!to_free->newsplit)
		return (-1);
	to_free->not_expend = ft_calloc(sizeof(char *), (count_split(split) + 1));
	if (!to_free->not_expend)
	{
		ft_free_strs(split);
		return (-1);
	}
	to_free->is_in_quote = ft_calloc(sizeof(char *), (count_split(split) + 1));
	if (!to_free->is_in_quote)
	{
		free(to_free->not_expend);
		free(to_free->is_in_quote);
		ft_free_strs(split);
		return (-1);
	}
	return (0);
}

int	trim_all(char **split, t_free *to_free)
{
	int				i;
	int				tmp;

	if (trim_all_2(split, to_free) == -1)
		return (-1);
	i = -1;
	while (split[++i])
	{
		tmp = 0;
		to_free->newsplit[i] = make_it_clean(split[i], tmp);
		if (!to_free->newsplit[i])
			return (free_trim_all(to_free, i));
		if (ft_strcmp(to_free->newsplit[i], split[i])
			&& check_if_expend(split[i]))
			to_free->not_expend[i] = true;
		if (check_if_in_quote(split[i]))
			to_free->is_in_quote[i] = true;
	}
	to_free->newsplit[i++] = NULL;
	free_split(split);
	return (0);
}
