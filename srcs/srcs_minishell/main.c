/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/02 14:25:59 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile int g_sig_int = 0;

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	show_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d = %s\n",i, (char *)list->content);
		i++;
		list = list->next;
	}
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
		if (g_sig_int == 1)
		{
			rl_redisplay();
			g_sig_int = 0;
			continue ;
		}
		add_history(save);
		list = ft_fill(save, &to_free);
		ft_echo_exec(list);
		free_split(to_free.split);
	}
	return (0);
}
