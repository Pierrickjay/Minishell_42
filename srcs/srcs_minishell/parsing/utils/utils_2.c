/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:45 by pjay              #+#    #+#             */
/*   Updated: 2023/03/09 13:33:19 by pjay             ###   ########.fr       */
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

void	ft_print_exeptected_token(char *str)
{
	ft_putstr_fd(SYNTAXE_ERROR, STDERR);
	ft_putstr_fd(" `", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putendl_fd("\'", STDERR);
}
