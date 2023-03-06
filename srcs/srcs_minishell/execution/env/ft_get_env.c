/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:21:18 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:18:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// return the value of the env variable
char	*ft_get_env(char *name, char **env)
{
	char	*value;
	size_t	len;
	size_t	i;

	len = ft_strlen((const char *)name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], len) == 0)
		{
			value = ft_get_value(env[i]);
			if (!value)
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
