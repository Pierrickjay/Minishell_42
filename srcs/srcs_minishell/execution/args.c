/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:59:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 10:42:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	ft_args_size(t_list *lst)
{
	size_t	size;

	size = 0;
	if (lst == NULL)
		return (size);
	while (lst && lst->type != CMD)
		lst = lst->next;
	if (lst->type == CMD)
	{
		size++;
		lst = lst->next;
	}
	while (lst && lst->type == OPT)
	{
		size++;
		lst = lst->next;
	}
	while (lst && lst->type == ARG)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

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
	i = 0;
	while (lst && lst->type != CMD)
		lst = lst->next;
	while (i < size)
	{
		args[i] = lst->content;
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
