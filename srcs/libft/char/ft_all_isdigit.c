/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:51:29 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 15:21:38 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

// check all the string if its digit return 1 else 0
int	ft_all_isdigit(char *str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i == len)
		return (1);
	return (0);
}
