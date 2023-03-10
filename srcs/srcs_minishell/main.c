/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:35:26 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 15:57:51 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	finish_syntaxe(char *save)
{
	ft_putendl_fd("syntaxe error", STDERR);
	free(save);
	return (-1);
}

int	check_synthaxe_error(char *save)
{
	int	i;

	i = 0;
	while (save[i])
	{
		if (save[i] && save[i] == '\'')
		{
			i++;
			while (save[i] && save[i] != '\'')
				i++;
		}
		else if (save[i] && save[i] == '\"')
		{
			i++;
			while (save[i] && save[i] != '\"')
				i++;
		}
		else if (save[i] && save[i] == ';')
			return (finish_syntaxe(save));
		else
			i++;
	}
	return (0);
}

int	is_full_of_space(char *save)
{
	int	i;

	i = 0;
	if (check_synthaxe_error(save) == -1)
		return (-1);
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
	static int		count_line = 0;

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
		ft_exit(list, envp, to_free, save);
		envp = main_exec(list, envp, &count_line);
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
