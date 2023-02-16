/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 12:12:58 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
bug a fixe :
premiere commande il y a un invalid write of size 8
 - gerer quand largs 2 est vide
*/
volatile int g_sig_int = 0;

void	free_all(char **split, char *save)
{
	free(save);
	free(split);
}


int	main(int ac, char **av, char **env)
{
	char	*save;
	t_list	*list;
	t_free	to_free;

	(void)ac;
	(void)av;
	create_siga();
	while (1)
	{
		save = readline("minishell>");
		if (save == NULL)
		{
			printf(("EOF enconter ctrl d pressed"));
			exit (0);
		}
		if (save[0] == '\0')
		{
			free(save);
			continue ;
		}
		add_history(save);
		list = ft_fill(save, &to_free);
		free_all(to_free.split, save);
		main_exec(list, env);
	}
	return (0);
}
