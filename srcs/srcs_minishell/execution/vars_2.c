/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:09:56 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/11 09:17:03 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// update the string when we have a lot dorlars and add space before dolars
char	*ft_content_update(char *str)
{
	size_t	nb_dolars;
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new_str;

	nb_dolars = ft_nb_var(str);
	len = ft_strlen(str);
	new_str = ft_calloc((nb_dolars + len + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			new_str[j++] = -1;
		new_str[j++] = str[i++];
	}
	ft_free((void **)&str);
	return (new_str);
}

char	*ft_check_envi(char *key, t_envi *envi)
{
	char	*value;

	if (ft_getenvi(key, envi) != NULL)
		value = ft_strdup(ft_getenvi(key, envi));
	else
		value = ft_strdup("\0");
	return (value);
}
