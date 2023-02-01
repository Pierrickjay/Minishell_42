/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:00:40 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/01 11:06:21 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo_exec(t_list *cmd, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd(cmd->next->next->content, STDOUT_FILENO);
	}
	else
	{
		ft_putendl_fd(cmd->content, STDOUT_FILENO);
	}
}
