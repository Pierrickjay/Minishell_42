/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_to_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:49:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 15:56:40 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	**ft_envi_to_env(t_envi *envi)
{
	char	**env;
	char	*tmp;
	size_t	i;
	size_t	size;

	size = ft_envi_size(envi);
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (envi->type == NORMAL)
		{
			tmp = ft_strjoin(envi->key, "=");
			if (!tmp)
				return (ft_free_strs_n(env, i), NULL);
			env[i] = ft_strjoin(tmp, envi->value);
			if (!env[i])
				return (ft_free_strs_n(env, i), NULL);
			ft_free((void **)&tmp);
			i++;
		}
		envi = envi->next;
	}
	env[i] = NULL;
	return (env);
}
