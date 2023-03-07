/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:39 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 13:41:42 by pjay             ###   ########.fr       */
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

// int	ft_split_empty(char **strs)
// {
// 	size_t	i;
// 	size_t	n;

// 	i = 0;
// 	n = 0;
// 	while (strs[i])
// 	{
// 		if (ft_strcmp(strs[i], "\0") == 0)
// 			n++;
// 		i++;
// 	}
// 	if (i == n)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

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
			new_str[j++] = ' ';
		new_str[j++] = str[i++];
	}
	ft_free((void **)&str);
	return (new_str);
}
