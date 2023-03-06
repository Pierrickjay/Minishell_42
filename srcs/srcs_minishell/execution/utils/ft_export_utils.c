/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:39 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 18:06:58 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_is_ident(int c)
{
	if (ft_isdigit(c) || c == '?' || c == '!' || c == '@' || c == '#')
		return (true);
	return (false);
}

int	ft_all_isalnum(char *str)
{
	size_t	i;
	size_t	n;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			n++;
		i++;
	}
	if (n == len)
		return (1);
	return (0);
}

int	ft_check_last_char(char *str, char c)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len - 1] == c)
		return (1);
	return (0);
}
