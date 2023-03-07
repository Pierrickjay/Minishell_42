/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:39 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 08:37:12 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_nb_args_child(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_check_last_char(char *str, char c)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len - 1] == c)
		return (1);
	return (0);
}

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

int	ft_split_empty(char **strs)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (strs[i])
	{
		if (ft_strcmp(strs[i], "\0") == 0)
			n++;
		i++;
	}
	if (i == n)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// duplicate the enviroment list
t_envi	*ft_dup_envi(t_envi *envi)
{
	t_envi	*dup;
	t_envi	*tmp;
	char	*key;
	char	*value;

	dup = NULL;
	while (envi)
	{
		key = ft_strdup(envi->key);
		value = ft_strdup(envi->value);
		if (!key || !value)
			return (ft_free_envi(dup), ft_msg_malloc("parent_1.c (29)"), NULL);
		tmp = ft_envi_new(key, value, envi->type);
		if (!tmp)
			return (NULL);
		ft_envi_add_back(&dup, tmp);
		envi = envi->next;
	}
	return (dup);
}
