/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:35:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 14:23:47 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*save;
	t_list	*list;
	t_free	to_free;

	save = NULL;
	list = NULL;
	(void)ac;
	(void)av;
	ft_putstr_fd(_COLOR_BLUE, STDOUT);
	ft_putendl_fd(MINISHELL, STDOUT);
	ft_putstr_fd(_COLOR_CYAN, STDOUT);
	ft_putendl_fd(BY, STDOUT);
	ft_putstr_fd(_COLOR_RESET, STDOUT);
	create_siga(MAIN);
	boucle_minishell(env, list, &to_free, save);
	return (0);
}
