/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/03 16:40:56 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"



int		count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = count_split(split);
	while (i--)
		free(split[i]);
	free(split);
}

char *create_space(void)
{
	char *newsplit;

	newsplit = malloc(sizeof(char) * 2);
	if (!newsplit)
		return (NULL);
	newsplit[0] = ' ';
	newsplit[1] = '\0';
	return (newsplit);

}

char	**trim_all(char **split)
{
	int		i;
	char	**newsplit;
	int		a;

	a = 0;
	newsplit = malloc(sizeof(char *) * count_split(split) + 1);
	printf("count split + 1 = %d\n", count_split(split) + 1);
	if (!newsplit)
		return (NULL);
	i = -1;
	while (split[++i + a])
	{
		if (split[i + a][0] == '\'' && split[i + 1 + a][0] == '\'')
		{
			newsplit[i] = create_space();
			if (!newsplit[i])
				return (NULL);
			a++;
		}
		else
			newsplit[i] = ft_strtrim(split[i + a], "'");
	}
	printf("i = %d\n", i);
	newsplit[i] = NULL;
	free_split(split);
	return (newsplit);
}

t_list	*ft_fill(char *str, t_free *free)
{
	int		i;
	t_list	*list;
	t_list	*tmp;

	tmp = NULL;
	list = NULL;
	i = 1;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	free->split = trim_all(ft_split(str, ' '));
	list->content = free->split[0];
	while (free->split[i])
	{
		tmp = ft_lstnew(free->split[i]);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	show_list(list);
	// free_split(to_free.split);
	return (list);
}
