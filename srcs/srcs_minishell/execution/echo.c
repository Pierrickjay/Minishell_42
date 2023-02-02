/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:00:40 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/01 11:49:11 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo_exec(t_list *cmd)
{
	if (cmd->next && ft_strcmp("-n", cmd->next->content) == 0)
	{
		if (cmd->next->next)
		{
			if (cmd->next->next->content)
				ft_lst_print(cmd->next->next, 0);
			else
				ft_putstr_fd("", STDOUT_FILENO);
		}
	}
	else
	{
		if (cmd->next)
		{
			if (cmd->next->content)
				ft_lst_print(cmd->next, 1);
			else
				ft_putendl_fd("", STDOUT_FILENO);
		}
	}
}
