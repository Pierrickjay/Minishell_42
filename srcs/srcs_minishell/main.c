/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:35:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 12:04:25 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_line = 0;

int	is_full_of_space(char *save)
{
	int	i;

	i = 0;
	while (save[i])
	{
		if (save[i] != ' ')
			return (0);
		i++;
	}
	free(save);
	return (-1);
}

int	boucle_minishell(char **env, t_list *list, t_free *to_free, char *save)
{
	static t_envi	*envp = NULL;

	envp = ft_env_to_envi(env);
	if (envp == FAIL)
		return (ft_msg_malloc("main.c (21)"), EXIT_FAILURE);
	while (1)
	{
		create_siga(MAIN);
		count_line++;
		save = readline("minishell> ");
		create_siga(PARENT);
		if (save_is_null(save, envp) == -1 || is_full_of_space(save) == -1)
			continue ;
		add_history(save);
		list = ft_fill(save, to_free);
		if (list == NULL)
			continue ;
		if (ft_check_list(list, to_free, save, envp) == EXIT_SUCCESS)
			continue ;
		free_all(to_free->split, save);
		ft_exit(list, envp);
		envp = main_exec(list, envp);
		if (envp == FAIL)
			return (ft_msg_malloc("main.c (39)"), EXIT_FAILURE);
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
