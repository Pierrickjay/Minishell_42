/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:35:59 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 11:37:00 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	**ft_dup_env(char **env)
{
	char	**dup;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	dup = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (env[i])
	{
		dup[i] = ft_strdup(env[i]);
		if (!dup[i])
			return (ft_free_strs_n(dup, i), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
