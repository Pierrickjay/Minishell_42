/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:46:36 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/01 10:01:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

//to find the char c in the string
char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	lenth;

	lenth = ft_strlen(s);
	i = 0;
	while (i <= lenth)
	{
		if (s[i] == (unsigned char)c)
			return (((char *)s) + i);
		i++;
	}
	return (0);
}
