/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:44:42 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 11:57:40 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_type_redir(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (REDIR);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (REDIR);
	return (-1);
}

int	ft_type(char *str, int prev)
{
	if (ft_type_redir(str) != -1)
		return (REDIR);
	else if (str[0] == '-')
		return (OPT);
	else if (str[0] == '$')
		return (VAR);
	else if (str[0] == '|')
		return (PIPE);
	else if (prev == REDIR)
		return (FILES);
	else if (prev == OPT || prev == VAR || prev == CMD || prev == ARG)
		return (ARG);
	else
		return (CMD);
}

void	ft_set_type(t_list *lst)
{
	int		previous_type;

	previous_type = -1;
	while (lst)
	{
		lst->type = ft_type(lst->content, previous_type);
		previous_type = lst->type;
		lst = lst->next;
	}
}
