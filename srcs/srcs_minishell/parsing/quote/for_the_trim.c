/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:35:25 by pjay              #+#    #+#             */
/*   Updated: 2023/03/01 15:51:55 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"


int		go_next_quote(char *str, char c)
{
	int i;

	i = -1;
	if (c == '\'')
	{
		while (str[++i])
			if (str[i] == '\'')
				return (i);
	}
	else
		while (str[++i])
			if (str[i] == '\"')
				return (i);
	return (i);
}

char	*make_it_clean(char *str)
{
	int		i;
	char	*new_one;

	i = -1;
	new_one = ft_strdup_modif(str, 0);
	if (!new_one)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			printf("i = %d before send his adress || str = %s\n", i, new_one);
			new_one = ft_strdup_modif(remove_single(new_one), 1);
			i += go_next_quote(&str[i], '\'');
			printf("i = %d after send his adress|| str = %s\n", i, new_one);
		}
		if (str[i] == '\"')
		{
			printf("i = %d before send his adress in double || str = %s\n", i, new_one);
			new_one = ft_strdup_modif(remove_double(new_one), 1);
			i += go_next_quote(&str[i], '\"');
			printf("i = %d before send his adress in double || str = %s\n", i, new_one);
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
		printf("enter to make it clean\n");
		newsplit[i] = make_it_clean(split[i + a]);
		//printf("new_split = %s\n next_split = %s", newsplit[i], split[i + 1 + a]);
		if (!newsplit[i])
			return (NULL);
	}
	newsplit[i++] = NULL;
	free_split(split);
	return (newsplit);
}
