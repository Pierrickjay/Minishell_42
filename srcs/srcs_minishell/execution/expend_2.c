/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:09:56 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/22 09:48:31 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// count the nb or dolars in the string
size_t	ft_nb_var(char *str)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nb++;
		i++;
	}
	return (nb);
}

//vars no print and not use for your minishell
int	ft_var_special(char c)
{
	if (ft_isdigit(c) || c == '?' || c == '!' || c == '@' || c == '#' \
		|| c == '&' || c == '\0' || c == '=' || c == '+' || c == '-' )
		return (true);
	return (false);
}

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

// give the value of the key in the envi if not found return string null
// and duplicate the value
char	*ft_check_envi(char *key, t_envi *envi)
{
	char	*value;

	if (ft_getenvi(key, envi) != NULL)
		value = ft_strdup(ft_getenvi(key, envi));
	else
		value = ft_strdup("\0");
	return (value);
}

int	find_dollad_pos(char *str)
{
	int	sen;

	sen = (int)ft_strlen(str);
	if (str[sen - 1] == '$')
		return (TRUE);
	return (FALSE);
}
