/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:59:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 13:36:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// count the number of arguments in the list CMD OPT ARG OPT
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
	while (lst && (lst->type == ARG))
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

static int	ft_check_space(t_list *lst)
{
	while (lst && lst->type != CMD)
		lst = lst->next;
	if (lst && lst->type == CMD)
	{
		if (ft_strcmp(lst->content, "export") == 0)
			return (0);
		if (ft_strchr(lst->content, ' '))
			return (1);
		lst = lst->next;
	}
	while (lst && lst->type == ARG)
	{
		if (ft_strchr(lst->content, ' '))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static char	*ft_lst_join_split_bis(t_list *lst, char *str)
{
	char	*tmp;

	while (lst && lst->type == ARG)
	{
		tmp = str;
		str = ft_strjoin(str, lst->content);
		if (!str)
			return (free(tmp), NULL);
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, " ");
		if (!str)
			return (free(tmp), NULL);
		free(tmp);
		lst = lst->next;
	}
	return (str);
}

static char	**ft_lst_join_split(t_list *lst)
{
	char	*str;
	char	**args;

	if (lst == NULL)
		return (NULL);
	str = ft_strjoin(lst->content, " ");
	if (!str)
		return (NULL);
	lst = lst->next;
	str = ft_lst_join_split_bis(lst, str);
	if (!str)
		return (NULL);
	args = ft_split(str, ' ');
	free(str);
	return (args);
}

// convert the list to an array of arguments
char	**ft_lst_to_args(t_list *lst)
{
	char	**args;
	size_t	size;
	size_t	i;

	if (lst == NULL)
		return (NULL);
	if (ft_check_space(lst))
		return (ft_lst_join_split(lst));
	size = ft_args_size(lst);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (lst && lst->type != CMD)
		lst = lst->next;
	while (lst && i < size)
	{
		args[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
