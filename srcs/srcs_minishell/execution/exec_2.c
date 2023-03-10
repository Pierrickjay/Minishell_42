/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:59:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 17:25:17 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

// set the type of the redirection
t_redir	ft_redir_type(char *str)
{
	if (ft_strcmp(str, ">\0") == 0)
		return (TRUNC);
	else if (ft_strcmp(str, ">>\0") == 0)
		return (APPEND);
	else if (ft_strcmp(str, "<\0") == 0)
		return (INFILE);
	else if (ft_strcmp(str, "<<\0") == 0)
		return (HEREDOC);
	return (FAILURE);
}

// get the list of redirections
t_list	*ft_lst_redir(t_list *lst)
{
	t_list	*redir;
	t_list	*new;

	redir = NULL;
	while (lst)
	{
		if (lst->type == REDIR && lst->next && lst->next->type == FILES)
		{
			new = ft_lstnew(lst->next->content, ft_redir_type(lst->content));
			if (!new)
				return (ft_free_redir(redir), NULL);
			ft_lstadd_back(&redir, new);
		}
		lst = lst->next;
	}
	return (redir);
}

// get the number of each type of redirection
void	ft_nb_redir_type(t_list *redir, t_exec *exec)
{
	exec->nb_redir_type[INFILE] = 0;
	exec->nb_redir_type[TRUNC] = 0;
	exec->nb_redir_type[APPEND] = 0;
	exec->nb_redir_type[HEREDOC] = 0;
	while (redir)
	{
		if (redir->type != FAILURE)
			exec->nb_redir_type[redir->type]++;
		redir = redir->next;
	}
}
