/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:12:31 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 20:16:13 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

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

// set the redir in struct exec if there is no command
int	ft_set_redir_no_cmd(t_shell *shell, t_list *lst, t_list **redir)
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
