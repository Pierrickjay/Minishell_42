/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:42:01 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:18:19 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// return the key of the env variable
char	*ft_get_key(char *env)
{
	int		len;
	char	*key;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = ft_substr(env, 0, len);
	if (!key)
		return (NULL);
	return (key);
}
