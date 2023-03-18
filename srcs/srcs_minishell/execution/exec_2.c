/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:59:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 14:00:51 by obouhlel         ###   ########.fr       */
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
	exec->infile = ft_calloc(sizeof(int), exec->nb + exec->no_cmd + 1);
	if (!exec->infile)
		return (EXIT_FAILURE);
	exec->outfile = ft_calloc(sizeof(int), exec->nb + exec->no_cmd + 1);
	if (!exec->outfile)
		return (EXIT_FAILURE);
	if (exec->no_cmd && ft_set_redir_no_cmd(exec, lst, exec->redir))
		return (EXIT_FAILURE);
	if (!exec->no_cmd && ft_set_redir(exec, lst, exec->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_set_redir(t_exec *exec, t_list *lst, t_list **redir)
{
	t_list	*new;
	char	*name;
	int		type[2];
	int		i;

	i = 0;
	ft_bzero(type, sizeof(int) * 2);
	while (lst && i <= exec->nb)
	{
		if (lst->type == REDIR && lst->next && lst->next->type == FILES)
		{
			name = lst->next->content;
			new = ft_lstnew(name, ft_redir_type(lst->content, type));
			if (!new)
				return (EXIT_FAILURE);
			ft_lstadd_back(&redir[i], new);
		}
		ft_check_next(exec, lst, type, &i);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_check_next(t_exec *exec, t_list *lst, int type[2], int *i)
{
	if (exec->nb == 0)
	{
		exec->infile[0] = ft_set_file(type, IN);
		exec->outfile[0] = ft_set_file(type, OUT);
	}
	else if (lst->type == PIPE || lst->next == NULL)
	{
		exec->infile[*i] = ft_set_file(type, IN);
		exec->outfile[*i] = ft_set_file(type, OUT);
		ft_bzero(type, sizeof(int) * 2);
		(*i)++;
	}
}

// set the 1 if I have infile or outfile, the mode its for infile or outfile
int	ft_set_file(int type[2], int mode)
{
	if (mode == IN)
	{
		if (type[IN] > 0)
			return (1);
	}
	else if (mode == OUT)
	{
		if (type[OUT] > 0)
			return (1);
	}
	return (0);
}

// set the type of the redirection
int	ft_redir_type(char *str, int type[2])
{
	if (ft_strcmp(str, ">\0") == 0)
	{
		type[OUT]++;
		return (TRUNC);
	}
	else if (ft_strcmp(str, ">>\0") == 0)
	{
		type[OUT]++;
		return (APPEND);
	}
	else if (ft_strcmp(str, "<\0") == 0)
	{
		type[IN]++;
		return (INFILE);
	}
	return (FAILURE);
}
