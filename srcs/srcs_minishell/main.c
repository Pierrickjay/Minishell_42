/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/22 12:07:39 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(char **split, char *save)
{
	free(save);
	free(split);
}

void	ft_exit(t_list *list, char *save)
{
	if (ft_strcmp(list->content, "exit") == 0)
	{
		free(save);
		ft_free_lst(list);
		exit (0);
	}
}

int	boucle_minishell(char **env, t_list *list, t_free *to_free, char *save)
{
	while (1)
	{
		save = readline("minishell> ");
		if (save == NULL)
			exit(0);
		if (save[0] == '\0')
		{
			free(save);
			continue ;
		}
		add_history(save);
		list = ft_fill(save, to_free);
		ft_exit(list, save);
		if (list == NULL)
		{
			free_all(to_free->split, save);
			ft_free_lst(list);
			continue ;
		}
		free_all(to_free->split, save);
		ft_free_vars(main_exec(list, env));
	}
}

int	main(int ac, char **av, char **env)
{
	char	*save;
	t_list	*list;
	t_free	to_free;

	save = NULL;
	list = NULL;
	(void)ac;
	(void)av;
	create_siga();
	boucle_minishell(env, list, &to_free, save);
	return (0);
}
