/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:47:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 12:58:04 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

//to duplicate the string
char	*ft_strdup(const char *s)
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
	return (dup);
}
