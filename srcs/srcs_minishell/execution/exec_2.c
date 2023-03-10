/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:59:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 16:58:54 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// get the list of redirections
int	ft_lst_redir_malloc(t_exec *exec, t_list *lst)
{
	if (exec->nb_redir == 0)
		return (EXIT_SUCCESS);
	exec->redir = ft_calloc(sizeof(t_list *), exec->nb + 1);
	if (!exec->redir)
		return (EXIT_FAILURE);
	exec->nb_redir_type = ft_calloc(sizeof(int *), exec->nb + 1);
	if (!exec->nb_redir_type)
		return (EXIT_FAILURE);
	exec->infile = ft_calloc(sizeof(int), exec->nb + 1);
	if (!exec->infile)
		return (EXIT_FAILURE);
	exec->outfile = ft_calloc(sizeof(int), exec->nb + 1);
	if (!exec->outfile)
		return (EXIT_FAILURE);
	if (ft_set_redir(exec, lst, exec->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_set_redir(t_exec *exec, t_list *lst, t_list **redir)
{
	t_list	*new;
	int		i;

	i = 0;
	while (lst && i <= exec->nb)
	{
		if (lst->type == REDIR && lst->next && lst->next->type == FILES)
		{
			new = ft_lstnew(lst->next->content, ft_redir_type(lst->content));
			if (!new)
				return (EXIT_FAILURE);
			ft_lstadd_back(&redir[i], new);
		}
		if (lst->type == PIPE || lst->next == NULL)
		{
			if (ft_nb_redir_type(exec, redir[i], i))
				return (EXIT_FAILURE);
			exec->infile[i] = ft_set_file(exec, i, IN);
			exec->outfile[i] = ft_set_file(exec, i, OUT);
			i++;
		}
		lst = lst->next;
	}
	redir[i] = NULL;
	return (EXIT_SUCCESS);
}

// set the 1 if I have infile or outfile, the mode its for infile or outfile
int	ft_set_file(t_exec *exec, int i, int mode)
{
	if (mode == IN)
	{
		if (exec->nb_redir_type[i][INFILE] || exec->nb_redir_type[i][HEREDOC])
			return (1);
	}
	else if (mode == OUT)
	{
		if (exec->nb_redir_type[i][TRUNC] || exec->nb_redir_type[i][APPEND])
			return (1);
	}
	return (0);
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
