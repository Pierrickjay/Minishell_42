/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:59:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 12:56:47 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// get the list of redirections
int	ft_lst_redir_malloc(t_exec *exec, t_list *lst)
{
	int	i;

	exec->redir = ft_calloc(sizeof(t_list *), exec->nb + 1 + 1);
	if (!exec->redir)
		return (EXIT_FAILURE);
	i = 0;
	while (i < 4)
	{
		exec->nb_redir_type[i] = ft_calloc(sizeof(int *), exec->nb + 1);
		if (!exec->nb_redir_type)
			return (EXIT_FAILURE);
		i++;
	}
	exec->infile = ft_calloc(sizeof(int *), exec->nb + 1);
	if (!exec->infile)
		return (EXIT_FAILURE);
	exec->outfile = ft_calloc(sizeof(int *), exec->nb + 1);
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
			ft_nb_redir_type(exec->nb_redir_type[i], redir[i]);
			exec->infile[i] = ft_set_file(exec->nb_redir_type[i], IN);
			exec->outfile[i] = ft_set_file(exec->nb_redir_type[i], OUT);
			i++;
		}
		lst = lst->next;
	}
	redir[i] = NULL;
	return (EXIT_SUCCESS);
}

// set the 1 if I have infile or outfile, the mode its for infile or outfile
int	ft_set_file(int *nb_redir_type, int mode)
{
	if (mode == IN)
	{
		if (nb_redir_type[INFILE] || nb_redir_type[HEREDOC])
			return (1);
	}
	else if (mode == OUT)
	{
		if (nb_redir_type[TRUNC] || nb_redir_type[APPEND])
			return (1);
	}
	return (0);
}

// get the number of each type of redirection
void	ft_nb_redir_type(int nb_redir_type[4], t_list *redir)
{
	nb_redir_type[INFILE] = 0;
	nb_redir_type[TRUNC] = 0;
	nb_redir_type[APPEND] = 0;
	nb_redir_type[HEREDOC] = 0;
	while (redir)
	{
		if (redir->type != FAILURE)
			nb_redir_type[redir->type]++;
		redir = redir->next;
	}
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
