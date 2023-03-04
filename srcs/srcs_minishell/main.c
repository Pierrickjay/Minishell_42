/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:35:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/04 22:36:32 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(char **split, char *save)
{
	free(save);
	free(split);
}

void	ft_exit(t_list *list, char *save, t_envi *envp)
{
	if (ft_strcmp(list->content, "exit") == 0)
	{
		if (list->next && list->next->next && \
			ft_isdigit(list->next->next->content[0]) == 1)
			return ;
		free(save);
		ft_free_lst(list);
		ft_free_envi(envp);
		ft_putendl_fd("exit", STDOUT);
		exit(0);
	}
}

int	ft_check_list(t_list *list, t_free *to_free, char *save, t_envi *envp)
{
	if (list == NULL)
	{
		free_all(to_free->split, save);
		ft_free_envi(envp);
		ft_free_lst(list);
		ft_putendl_fd("exit", STDOUT);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	boucle_minishell(char **env, t_list *list, t_free *to_free, char *save)
{
	static t_envi	*envp = NULL;

	envp = ft_env_to_envi(env);
	if (!envp)
		return (ft_msg(NULL, NULL, MA, NULL), EXIT_FAILURE);
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
