/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:44:42 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 15:37:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// int	check_tiret(char *str)
// {
// 	int	i;
// 	int count;

// 	i = 1;
// 	count = 0;

// 	while (str[i])
// 	{
// 		if (str[i] == '-' )
// 			count++;
// 	}
// }

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
	else if (str[0] == '|')
		return (PIPE);
	else if (prev == REDIR)
		return (FILES);
	else if (prev == CMD || prev == ARG)
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
		if (lst->type == -1)
			lst->type = ft_type(lst->content, previous_type);
		previous_type = lst->type;
		lst = lst->next;
	}
}
