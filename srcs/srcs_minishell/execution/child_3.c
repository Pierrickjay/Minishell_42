/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:11:07 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 11:49:58 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// no cmd but redirection
void	ft_exec_child_no_cmd(t_exec *exec)
{
	const int	n = exec->i;
	int			fd_in;
	int			fd_out;

	fd_in = ft_open_infiles(exec->redir[n], exec->nb_redir_type[n][HEREDOC], \
							exec->count_line, exec);
	if (fd_in == FAILURE)
		return (ft_msg(exec, NULL, errno, &exit));
	ft_close(&fd_in);
	fd_out = ft_open_outfiles(exec->redir[n], exec->count_line, exec);
	if (fd_out == FAILURE)
		return (ft_msg(exec, NULL, errno, &exit));
	ft_close(&fd_out);
	ft_free_exec(exec);
	exit(EXIT_SUCCESS);
}
