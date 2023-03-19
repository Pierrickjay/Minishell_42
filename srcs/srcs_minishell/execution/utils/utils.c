/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:32:11 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 10:39:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// count the length of the char ** array
int	ft_nb_args_child(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

// check if the last char of the string is c
int	ft_check_last_char(char *str, char c)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len - 1] == c)
		return (1);
	return (0);
}

// check if the string is composed of only alphanumerical characters
int	ft_all_isalnum(char *str)
{
	size_t	i;
	size_t	n;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			n++;
		i++;
	}
	if (n == len)
		return (1);
	return (0);
}

// check if the string is composed of only alphanumerical characters
// with the length
int	ft_all_isalnum_len(char *str, int len)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i] && i < len)
	{
		if (ft_isalnum(str[i]))
			n++;
		i++;
	}
	if (n == len)
		return (1);
	return (0);
}

// duplicate the enviroment list
// if envi est une modif pour norm
t_envi	*ft_dup_envi(t_envi *envi)
{
	t_envi	*dup;
	t_envi	*tmp;
	char	*key;
	char	*value;

	if (envi == NULL)
		return (NULL);
	dup = NULL;
	while (envi)
	{
		key = ft_strdup(envi->key);
		value = ft_strdup(envi->value);
		if (!key || !value)
			return (ft_free_envi(dup), ft_msg_malloc("ft_dup_envi (95)"), NULL);
		tmp = ft_envi_new(key, value, envi->type);
		if (!tmp)
			return (NULL);
		ft_envi_add_back(&dup, tmp);
		envi = envi->next;
	}
	return (dup);
}
