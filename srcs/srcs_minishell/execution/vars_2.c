/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:59:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/21 15:00:13 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

t_redir	ft_redir_type(char *str)
{
	if (ft_strncmp(str, ">\0", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(str, ">>\0", 3) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(str, "<\0", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(str, "<<\0", 3) == 0)
		return (REDIR_HEREDOC);
	return (FAILURE);
}

t_list	*ft_lst_redir(t_list *lst)
{
	t_list	*redir;

	redir = NULL;
	while (lst)
	{
		if (lst->type == REDIR && lst->next && lst->next->type == FILES)
			ft_lstadd_back(&redir, ft_lstnew(lst->next->content, \
							ft_redir_type(lst->content)));
		lst = lst->next;
	}
	return (redir);
}

void	ft_nb_redir_type(t_list *redir, t_vars *vars)
{
	vars->nb_redir_type[REDIR_IN] = 0;
	vars->nb_redir_type[REDIR_OUT] = 0;
	vars->nb_redir_type[REDIR_APPEND] = 0;
	vars->nb_redir_type[REDIR_HEREDOC] = 0;
	while (redir)
	{
		if (redir->type != FAILURE)
			vars->nb_redir_type[redir->type]++;
		redir = redir->next;
	}
}
