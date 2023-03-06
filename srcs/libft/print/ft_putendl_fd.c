/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:43:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 14:14:18 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	if (ft_putstr_fd(s, fd))
		return (EXIT_FAILURE);
	if (ft_putchar_fd('\n', fd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
