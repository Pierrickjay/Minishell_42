/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_to_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:49:53 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 15:22:42 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// split of ft_envi_to_env
static int	ft_envi_to_env_bis(char **env, t_envi *envi, size_t i)
{
	char	*tmp;

	tmp = ft_strjoin(envi->key, "=");
	if (!tmp)
		return (ft_free_strs_n(env, i), EXIT_FAILURE);
	env[i] = ft_strjoin(tmp, envi->value);
	if (!env[i])
		return (ft_free_strs_n(env, i), EXIT_FAILURE);
	ft_free((void **)&tmp);
	return (EXIT_SUCCESS);
}

// convert a t_envi list to a char **env
char	**ft_envi_to_env(t_envi *envi)
{
	char	**env;
	size_t	i;
	size_t	size;

	if (!envi)
		return (NULL);
	size = ft_envi_size(envi);
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (FAIL);
	i = 0;
	while (i < size)
	{
		if (envi->type == NORMAL)
		{
			if (ft_envi_to_env_bis(env, envi, i) == EXIT_FAILURE)
				return (FAIL);
			i++;
		}
		envi = envi->next;
	}
	env[i] = NULL;
	return (env);
}
