/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/01 11:53:50 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(char **split, char *save)
{
	free(save);
	free(split);
}

void	ft_exit(t_list *list, char *save, char **envp)
{
	if (ft_strcmp(list->content, "exit") == 0)
	{
		free(save);
		ft_free_lst(list);
		ft_free_strs(envp);
		ft_putendl_fd("exit", STDOUT);
		exit(0);
	}
}

int	ft_check_list(t_list *list, t_free *to_free, char *save, char **envp)
{
	if (list == NULL)
	{
		free_all(to_free->split, save);
		ft_free_strs(envp);
		ft_free_lst(list);
		ft_putendl_fd("exit", STDOUT);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	boucle_minishell(char **env, t_list *list, t_free *to_free, char *save)
{
	static char	**envp = NULL;

	envp = ft_dup_env(env);
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
	create_siga();
	boucle_minishell(env, list, &to_free, save);
	return (0);
}
