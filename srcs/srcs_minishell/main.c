/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/03 12:40:19 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	boucle_minishell(char **env, t_list *list, t_free *to_free, char *save)
{
	static char	**envp = NULL;

	envp = ft_dup_env(env);
	while (1)
	{
		create_siga(MAIN);
		save = readline("minishell> ");
		create_siga(PARENT);
		if (save_is_null(save) == -1)
			continue ;
		add_history(save);
		list = ft_fill(save, to_free);
		if (list == NULL)
			continue ;
		ft_exit(list, save, envp);
		if (ft_check_list(list, to_free, save, envp) == EXIT_SUCCESS)
			continue ;
		free_all(to_free->split, save);
		ft_lst_print_type(list);
		envp = main_exec(list, envp);
		if (!envp)
			return (ft_msg(NULL, NULL, MA, NULL), EXIT_FAILURE);
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
	create_siga(MAIN);
	boucle_minishell(env, list, &to_free, save);
	return (0);
}
