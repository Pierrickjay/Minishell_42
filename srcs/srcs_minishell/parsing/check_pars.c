/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:52:17 by pjay              #+#    #+#             */
/*   Updated: 2023/03/07 10:26:24 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_redir_nb(t_list *lst)
{
	const t_list	*tmp = lst;
	int				i;

	while (lst)
	{
		if (lst->type == REDIR)
		{
			i = 0;
			while (lst->content[i])
			{
				if (i > 1)
				{
					if (lst->content[0] == '>')
						ft_print_exeptected_token(">");
					else
						ft_print_exeptected_token("<");
					ft_free_lst((t_list *)tmp);
					return (-1);
				}
				i++;
			}
		}
		lst = lst->next;
	}
	return (0);
}


int	check_arrow_pipe(t_list *lst)
{
	const t_list	*tmp = lst;
	int				type;

	type = lst->type;
	lst = lst->next;
	while (lst)
	{
		if (lst->type == type)
		{
			if (type == PIPE)
			{
				ft_print_exeptected_token(lst->content);
				return (ft_free_lst((t_list *)tmp), -1);
			}
			if (type == REDIR)
			{
				ft_print_exeptected_token(lst->content);
				return (ft_free_lst((t_list *)tmp), -1);
			}
		}
		type = lst->type;
		lst = lst->next;
	}
	return (0);
}
