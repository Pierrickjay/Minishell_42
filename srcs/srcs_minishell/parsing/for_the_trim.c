/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:35:25 by pjay              #+#    #+#             */
/*   Updated: 2023/02/23 14:22:26 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_next_spe(char **split, char **newsplit, int i, int a)
{
	int	e;

	e = -1;
	if ((split[i + a][0] == '\'' && split[i + a][1] == '\'')
		|| (split[i + a][0] == '\"' && split[i + a][1] == '\"'))
	{
		newsplit[i] = create_space();
		if (!newsplit[i])
		{
			while (split[++e])
				free(split[e]);
			free(split);
			i = 0;
			while (i >= 0)
				free(newsplit[i++]);
			free(newsplit);
			exit (0);
		}
		return (1);
	}
	return (0);
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
		if (!(check_next_spe(split, newsplit, i, a) == 0))
			a++;
		else
		{
			newsplit[i] = make_it_clean(split[i + a]);
			if (!newsplit[i])
				return (NULL);
		}
	}
	newsplit[i++] = NULL;
	free_split(split);
	return (newsplit);
}
