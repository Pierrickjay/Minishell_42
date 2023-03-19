/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:59:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/19 09:54:20 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// count the number of arguments in the list CMD OPT ARG OPT
size_t	ft_args_size(t_list *lst)
{
	int		space;
	size_t	size;

	size = 0;
	space = FALSE;
	if (lst == NULL)
		return (size);
	if (ft_space_in_cmd(lst))
		space = TRUE;
	while (lst && lst->type != CMD)
		lst = lst->next;
	if (lst->type == CMD)
	{
		size++;
		lst = lst->next;
	}
	while (lst && (lst->type == ARG))
	{
		size++;
		lst = lst->next;
	}
	return (size + space);
}

int	ft_space_in_cmd(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && lst->type != CMD)
		lst = lst->next;
	if (lst && lst->type == CMD)
	{
		while (lst->content[i])
		{
			if (lst->content[i] == ' ')
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}

int	ft_strlen_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	return (len);
}

int	ft_split_at_space_cmd(t_list *lst, char **args, size_t *i)
{
	if (lst->type == CMD && ft_strchr(lst->content, ' '))
	{
		args[*i] = ft_substr(lst->content, 0, ft_strlen_space(lst->content));
		if (!args[*i])
			return (ft_free_strs_n(args, *i), EXIT_FAILURE);
		(*i)++;
		args[*i] = ft_substr(lst->content, ft_strlen_space(lst->content) + 1,
				ft_strlen(lst->content) - ft_strlen_space(lst->content));
		if (!args[*i])
			return (ft_free_strs_n(args, *i), EXIT_FAILURE);
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

// convert the list to an array of arguments
char	**ft_lst_to_args(t_list *lst)
{
	char	**args;
	size_t	size;
	size_t	i;

	if (lst == NULL)
		return (NULL);
	size = ft_args_size(lst);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (lst && lst->type != CMD)
		lst = lst->next;
	i = 0;
	if (ft_split_at_space_cmd(lst, args, &i))
		return (NULL);
	while (lst && i < size)
	{
		args[i] = ft_strdup(lst->content);
		if (!args[i])
			return (ft_free_strs_n(args, i), NULL);
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
