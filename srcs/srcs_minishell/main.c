/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/14 14:25:58 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
bug a fixe :
premiere commande il y a un invalid write of size 8
 - gerer quand largs 2 est vide
*/
volatile int g_sig_int = 0;

void	free_all(char **split, char *save, t_list *list)
{
	free(save);
	ft_lstclear(&list, free);
	free(split);
}


int	main(void)
{
	char	*save;
	t_list	*list;
	t_free	to_free;

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
		if (ft_strcmp(list->content, "echo") == 0)
			ft_echo_exec(list);
		free_all(to_free.split, save, list);
	}
	return (0);
}
