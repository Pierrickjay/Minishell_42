/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/03 16:38:43 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
bug a fixe :
premiere commande il y a un invalid write of size 8
*/
volatile int g_sig_int = 0;

void	free_all(char **split, char *save, t_list *list)
{
	free(save);
	ft_lstclear(&list, free);
	free(split);
}

void	show_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d = %s\n",i, list->content);
		i++;
		list = list->next;
	}
}

int	main(void) // invalide read apres une commande puis espace
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
			//free_split(to_free.split);
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
