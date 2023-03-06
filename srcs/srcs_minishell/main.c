/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:35:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 10:08:28 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	boucle_minishell(char **env, t_list *list, t_free *to_free, char *save)
{
	static t_envi	*envp = NULL;

	envp = ft_env_to_envi(env);
	if (!envp)
		return (ft_msg_malloc("parent_1.c (21)"), EXIT_FAILURE);
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
		envp = main_exec(list, envp);
		if (!envp)
			return (ft_msg_malloc("parent_1.c (39)"), EXIT_FAILURE);
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
