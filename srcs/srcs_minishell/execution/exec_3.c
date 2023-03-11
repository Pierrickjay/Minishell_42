/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:12:31 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/11 10:27:03 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// count the number of redirection in the list
size_t	ft_nb_redir(t_list *lst)
{
	size_t	nb;

	nb = 0;
	while (lst)
	{
		if (lst->type == REDIR)
			nb++;
		lst = lst->next;
	}
	return (nb);
}

// count the number of commands in the list
size_t	ft_nb_cmds(t_list *lst)
{
	size_t	nb;

	nb = 0;
	while (lst)
	{
		if (lst->type == CMD)
			nb++;
		lst = lst->next;
	}
	return (nb);
}

int	ft_set_redir_no_cmd(t_exec *exec, t_list *lst, t_list **redir)
{
	t_list	*new;

	while (lst)
	{
		if (lst->type == REDIR && lst->next && lst->next->type == FILES)
		{
			new = ft_lstnew(lst->next->content, ft_redir_type(lst->content));
			if (!new)
				return (EXIT_FAILURE);
			ft_lstadd_back(&redir[0], new);
		}
		lst = lst->next;
	}
	if (ft_nb_redir_type(exec, redir[0], 0))
		return (EXIT_FAILURE);
	exec->infile[0] = ft_set_file(exec, 0, IN);
	exec->outfile[0] = ft_set_file(exec, 0, OUT);
	return (EXIT_SUCCESS);
}
