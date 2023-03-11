/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:14:38 by pjay              #+#    #+#             */
/*   Updated: 2023/03/11 09:39:19 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile int	g_check;

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
		if (save[i] && save[i] == '\'' && i++)
		{
			while (save[i] && save[i] != '\'')
				i++;
			if (!save[i])
				return (finish_syntaxe(save));
		}
		else if (save[i] && save[i] == '\"' && i++)
		{
			while (save[i] && save[i] != '\"')
				i++;
			if (!save[i])
				return (finish_syntaxe(save));
		}
		if (save[i] && (save[i] == ';' || save[i] == 92))
			return (finish_syntaxe(save));
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

char	*ft_readline(char *save, int *count_line, t_envi *envp, int *exit_code)
{
	g_check = 0;
	create_siga(MAIN);
	(*count_line)++;
	save = readline("minishell> ");
	add_history(save);
	if (g_check == 2)
		*exit_code = 130;
	create_siga(PARENT);
	if (save_is_null(save, envp) == -1 || is_full_of_space(save) == -1)
		return (NULL);
	return (save);
}

int	boucle_minishell(char **env, t_list *list, t_free *to_free, char *save)
{
	static t_envi	*envp = NULL;
	static int		count_line = 0;
	static int		exit_code = 0;

	envp = ft_env_to_envi(env);
	if (envp == FAIL)
		return (ft_msg_malloc("main.c (21)"), EXIT_FAILURE);
	while (1)
	{
		save = ft_readline(save, &count_line, envp, &exit_code);
		if (save == NULL)
			continue ;
		list = ft_fill(save, to_free);
		if (list == NULL)
			continue ;
		if (ft_check_list(list, to_free, save, envp) == EXIT_SUCCESS)
			continue ;
		ft_exit(list, envp, to_free, save);
		envp = main_exec(list, envp, &count_line, &exit_code);
		if (envp == FAIL)
			return (ft_msg_malloc("main.c (39)"), EXIT_FAILURE);
	}
}
