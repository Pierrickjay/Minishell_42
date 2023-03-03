/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:54:24 by pjay              #+#    #+#             */
/*   Updated: 2023/03/03 09:25:55 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	*ft_erase_all(char **str_dup, t_list *list, char *str)
{
	if (str_dup)
	{
		ft_putendl_fd("synthaxe error", 2);
		ft_free_strs(str_dup);
	}
	free(list);
	free(str);
	return (NULL);
}

t_list	*ft_fill_2(t_free *to_free, t_list *list)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	list->content = to_free->split[0];
	while (to_free->split[i])
	{
		tmp = ft_lstnew(to_free->split[i], -1);
		if (tmp == NULL)
			return (NULL);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	ft_set_type(list);
	return (list);
}

void	print_string(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("print split %s\n", str[i]);
		i++;
	}
}

t_list	*ft_fill(char *str, t_free *to_free)
{
	t_list	*list;
	char	**str_dup;

	list = NULL;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	if (check_order_quote(str) == -1)
	{
		ft_putendl_fd("synthaxe error", 2);
		free(str);
		return (NULL);
	}
	str_dup = split_parsing(str, ' ');
	//print_string(str_dup);
	if (!str_dup || count_quote(str_dup))
		return (ft_erase_all(str_dup, list, str));
	to_free->split = trim_all(str_dup);
	if (!to_free->split || !(to_free->split[0]))
	{
		free(list);
		return (NULL);
	}
	list = ft_fill_2(to_free, list);
	ft_lst_print_type(list);
	if (!list)
		return (NULL);
	return (list);
}
