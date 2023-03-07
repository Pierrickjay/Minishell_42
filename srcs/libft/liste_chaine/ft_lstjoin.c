/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:50:44 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 18:21:53 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static size_t	ft_lstjoin_len(t_list *to_join)
{
	size_t	len;

	len = 0;
	while (to_join)
	{
		len += ft_strlen(to_join->content);
		to_join = to_join->next;
	}
	return (len);
}

char	*ft_lstjoin(t_list *to_join)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_lstjoin_len(to_join);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (to_join)
	{
		j = 0;
		len = ft_strlen(to_join->content);
		while (j < len)
		{
			str[i] = to_join->content[j];
			i++;
			j++;
		}
		to_join = to_join->next;
	}
	str[i] = '\0';
	return (str);
}
