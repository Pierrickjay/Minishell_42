/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:07:08 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 13:20:01 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// get the old pwd and pwd and update the enviroment
static int	ft_cd_4(t_exec *exec, char *pwd, char *old_pwd)
{
	size_t	len;

	len = ft_strlen(old_pwd);
	while (old_pwd[len] != '/')
		len--;
	pwd = (char *)malloc(sizeof(char) * (len + 1));
	if (!pwd)
		return (EXIT_FAILURE);
	ft_strlcpy(pwd, old_pwd, len + 1);
	exec->envi = ft_envi_update_value("PWD", pwd, 0, exec->envi);
	if (!exec->envi)
		return (EXIT_FAILURE);
	free(pwd);
	return (EXIT_SUCCESS);
}

// get the old pwd and pwd and update the enviroment
static int	ft_cd_3(t_exec *exec, char *pwd, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;

	tmp = ft_strjoin("/", pwd);
	new_pwd = ft_strjoin(old_pwd, tmp);
	if (!new_pwd)
		return (EXIT_FAILURE);
	free(tmp);
	exec->envi = ft_envi_update_value("PWD", new_pwd, 0, exec->envi);
	if (!exec->envi)
		return (EXIT_FAILURE);
	free(new_pwd);
	return (EXIT_SUCCESS);
}

// get the old pwd and pwd and update the enviroment
static int	ft_cd_2(t_exec *exec, char *pwd, char *old_pwd)
{
	size_t	len;

	len = ft_strlen(pwd);
	if (ft_strncmp(pwd, old_pwd, len) != 0 && ft_cd_3(exec, pwd, old_pwd))
		return (EXIT_FAILURE);
	else if (ft_strcmp("..", pwd) == 0 || ft_strcmp(".", pwd) == 0)
	{
		if (ft_cd_4(exec, pwd, old_pwd))
			return (EXIT_FAILURE);
	}
	else
	{
		exec->envi = ft_envi_update_value("PWD", pwd, 0, exec->envi);
		if (!exec->envi)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// get the old pwd and pwd and update the enviroment
static int	ft_cd_1(t_exec *exec, char *pwd)
{
	char	*old_pwd;

	old_pwd = ft_strdup(ft_getenvi("PWD", exec->envi));
	if (!old_pwd)
		return (EXIT_FAILURE);
	if (ft_cd_2(exec, pwd, old_pwd))
		return (EXIT_FAILURE);
	exec->envi = ft_envi_update_value("OLDPWD", old_pwd, 0, exec->envi);
	if (!exec->envi)
		return (EXIT_FAILURE);
	ft_free_strs(exec->env);
	exec->env = ft_envi_to_env(exec->envi);
	if (!exec->env)
		return (EXIT_FAILURE);
	free(old_pwd);
	return (EXIT_SUCCESS);
}

// return exit code and print error message and main of cd
int	ft_cd(t_exec *exec)
{
	const char	**args = (const char **)exec->args[exec->i];
	char		*pwd;

	if (!args[1])
	{
		pwd = ft_getenvi("HOME", exec->envi);
		if (!pwd)
			return (ft_msg_builtins("cd", NULL, HOME), 1);
		if (access(pwd, F_OK) == FAILURE)
			return (ft_msg_builtins("cd", pwd, PERM), 1);
		if (chdir(pwd) == FAILURE)
			return (ft_msg(NULL, pwd, errno, NULL), 1);
		if (ft_cd_1(exec, pwd))
			return (ft_msg(NULL, NULL, MA, NULL), 1);
	}
	else
	{
		if (access(args[1], F_OK) == FAILURE)
			return (ft_msg_builtins("cd", (char *)args[1], PERM), 1);
		if (chdir(args[1]) == FAILURE)
			return (ft_msg_builtins("cd", (char *)args[1], PERM), 1);
		if (ft_cd_1(exec, (char *)args[1]))
			return (ft_msg(NULL, NULL, MA, NULL), 1);
	}
	return (EXIT_SUCCESS);
}
