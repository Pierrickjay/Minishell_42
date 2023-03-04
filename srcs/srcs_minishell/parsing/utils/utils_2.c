/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:45 by pjay              #+#    #+#             */
/*   Updated: 2023/03/03 12:24:33 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	*ft_strdup_modif(char *s, int to_free)
{
	char	*dup;
	size_t	lenth;
	size_t	i;

	lenth = ft_strlen(s);
	dup = (char *)malloc((lenth + 1) * sizeof(char));
	if (!dup)
		return (0);
	i = 0;
	while (i < lenth)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	if (to_free == 1)
		free(s);
	return (dup);
}

void	print_string(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("print split %s\n", str[i]);
		i++;
	}
}
