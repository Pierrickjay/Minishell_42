/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:59:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/14 07:12:18 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// get the list of redirections
int	ft_lst_redir_malloc(t_exec *exec, t_list *lst)
{
	if (exec->nb_redir == 0)
		return (EXIT_SUCCESS);
	if (exec->nb == 0)
		exec->no_cmd = 1;
	exec->redir = ft_calloc(sizeof(t_list *), exec->nb + exec->no_cmd + 1);
	if (!exec->redir)
		return (EXIT_FAILURE);
	exec->nb_redir_type = ft_calloc(sizeof(int *), exec->nb + exec->no_cmd + 1);
	if (!exec->nb_redir_type)
		return (EXIT_FAILURE);
	exec->infile = ft_calloc(sizeof(int), exec->nb + exec->no_cmd + 1);
	if (!exec->infile)
		return (EXIT_FAILURE);
	exec->outfile = ft_calloc(sizeof(int), exec->nb + exec->no_cmd + 1);
	if (!exec->outfile)
		return (EXIT_FAILURE);
	exec->heredoc = ft_calloc(sizeof(int), exec->nb + exec->no_cmd + 1);
	if (!exec->heredoc)
		return (EXIT_FAILURE);
	if (exec->no_cmd && ft_set_redir_no_cmd(exec, lst, exec->redir))
		return (EXIT_FAILURE);
	if (!exec->no_cmd && ft_set_redir(exec, lst, exec->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_set_redir(t_exec *exec, t_list *lst, t_list **redir)
{
	t_list	*new_redir;
	t_hdoc	*new_heredoc;
	int		redir_type;
	int		i;

	i = 0;
	while (lst && i <= exec->nb)
	{
		if (lst->type == REDIR && lst->next && lst->next->type == FILES)
		{
			redir_type = ft_redir_type(lst->content);
			if (redir_type == HEREDOC)
			{
				new_heredoc = ft_heredoc_new(lst->next->content, -1, i);
				if (!new_heredoc)
					return (EXIT_FAILURE);
				ft_lstadd_back(&exec->heredoc_lst, new_heredoc);
			}
			else
			{
				new_redir = ft_lstnew(lst->next->content, redir_type);
				if (!new_redir)
					return (EXIT_FAILURE);
				ft_lstadd_back(&redir[i], new_redir);
			}
		}
		if (lst->type == PIPE || lst->next == NULL)
		{
			if (ft_nb_redir_type(exec, redir[i], i))
				return (EXIT_FAILURE);
			exec->infile[i] = ft_set_file(exec, i, IN);
			exec->outfile[i] = ft_set_file(exec, i, OUT);
			exec->heredoc[i] = ft_set_file(exec, i, HEREDOC);
			i++;
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

// get the number of each type of redirection
int	ft_nb_redir_type(t_exec *exec, t_list *redir, int i)
{
	exec->nb_redir_type[i] = malloc(sizeof(int) * 4);
	if (!exec->nb_redir_type[i])
		return (EXIT_FAILURE);
	exec->nb_redir_type[i][INFILE] = 0;
	exec->nb_redir_type[i][TRUNC] = 0;
	exec->nb_redir_type[i][APPEND] = 0;
	exec->nb_redir_type[i][HEREDOC] = 0;
	while (redir)
	{
		if (redir->type != FAILURE)
			exec->nb_redir_type[i][redir->type]++;
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}

// set the type of the redirection
int	ft_redir_type(char *str)
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
