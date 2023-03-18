/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:59:49 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 20:16:15 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// get the list of redirections
int	ft_lst_redir_malloc(t_shell *shell, t_list *lst)
{
	int	n_bit;

	if (shell->nb_redir == 0)
		return (EXIT_SUCCESS);
	if (shell->nb_cmd == 0)
		shell->no_cmd = 1;
	n_bit = shell->nb_cmd + shell->no_cmd + 1;
	shell->redir = ft_calloc(sizeof(t_list *), n_bit);
	if (!shell->redir)
		return (EXIT_FAILURE);
	shell->infile = ft_calloc(sizeof(int), n_bit);
	if (!shell->infile)
		return (EXIT_FAILURE);
	shell->outfile = ft_calloc(sizeof(int), n_bit);
	if (!shell->outfile)
		return (EXIT_FAILURE);
	if (shell->no_cmd && ft_set_redir_no_cmd(shell, lst, shell->redir))
		return (EXIT_FAILURE);
	if (!shell->no_cmd && ft_set_redir(shell, lst, shell->redir))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_set_redir(t_shell *shell, t_list *lst, t_list **redir)
{
	t_list	*new;
	char	*name;
	int		type[2];
	int		i;

	i = 0;
	ft_bzero(type, sizeof(int) * 2);
	while (lst && i <= shell->nb_cmd)
	{
		if (lst->type == REDIR && lst->next && lst->next->type == FILES)
		{
			name = lst->next->content;
			new = ft_lstnew(name, ft_redir_type(lst->content, type));
			if (!new)
				return (EXIT_FAILURE);
			ft_lstadd_back(&redir[i], new);
		}
		ft_check_next(shell, lst, type, &i);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_check_next(t_shell *shell, t_list *lst, int type[2], int *i)
{
	if (shell->nb_cmd == 0)
	{
		shell->infile[0] = ft_set_file(type, IN);
		shell->outfile[0] = ft_set_file(type, OUT);
	}
	else if (lst->type == PIPE || lst->next == NULL)
	{
		shell->infile[*i] = ft_set_file(type, IN);
		shell->outfile[*i] = ft_set_file(type, OUT);
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
	else if (ft_strcmp(str, "<\0") == 0 || ft_strcmp(str, "<<\0") == 0)
	{
		type[IN]++;
		return (INFILE);
	}
	return (FAILURE);
}
