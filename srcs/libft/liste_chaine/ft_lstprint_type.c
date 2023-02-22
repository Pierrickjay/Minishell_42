/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:17:21 by pjay              #+#    #+#             */
/*   Updated: 2023/02/22 11:18:10 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static char	*ft_print_type(int type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == OPT)
		return ("OPT");
	else if (type == ARG)
		return ("ARG");
	else if (type == VAR)
		return ("VAR");
	else if (type == REDIR)
		return ("REDIR");
	else if (type == FILES)
		return ("FILES");
	else if (type == PIPE)
		return ("PIPE");
	else
		return ("UNKNOWN");
}

void	ft_lst_print_type(t_list *lst)
{
	if (lst == NULL)
		ft_putendl_fd("(null)", 1);
	while (lst)
	{
		printf("%s | %s\n", lst->content, ft_print_type(lst->type));
		lst = lst->next;
	}
}
