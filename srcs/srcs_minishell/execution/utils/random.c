/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:12:06 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/22 08:43:20 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// change the char to a printable char and return it
static int	ft_change_char(int c)
{
	if (c < 0)
		c = -c;
	while (c > 122)
		c -= 26;
	if (c < 32)
		c += 32;
	if (c == ' ')
		c = '_';
	if (c == '/')
		c = '_';
	if (c == '.')
		c = '_';
	if (c == '$')
		c = '_';
	return (c);
}

// malloc a random string with nb_char characters
// return the string or NULL if an error occured
char	*ft_random(int nb_char)
{
	int		fd_random;
	char	*buf;
	int		i;

	buf = ft_calloc(nb_char + 1, sizeof(char));
	if (!buf)
		return (NULL);
	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (NULL);
	if (read(fd_random, buf, nb_char) == -1)
		return (NULL);
	i = 0;
	while (i < (nb_char))
	{
		buf[i] = ft_change_char(buf[i]);
		i++;
	}
	close(fd_random);
	return (buf);
}
