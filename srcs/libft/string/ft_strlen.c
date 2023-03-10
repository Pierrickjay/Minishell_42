/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:51:29 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 10:14:28 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

//to calculate the lenth of the string

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
