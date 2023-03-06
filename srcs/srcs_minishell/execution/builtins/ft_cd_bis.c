/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:16:32 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/06 15:24:15 by obouhlel         ###   ########.fr       */
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
	if (exec->envi == FAIL)
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
	if (exec->envi == FAIL)
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
		if (exec->envi == FAIL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// get the old pwd and pwd and update the enviroment
int	ft_cd_1(t_exec *exec, char *pwd)
{
	char	*old_pwd;

	old_pwd = ft_strdup(ft_getenvi("PWD", exec->envi));
	if (!old_pwd)
		return (EXIT_FAILURE);
	if (ft_cd_2(exec, pwd, old_pwd))
		return (EXIT_FAILURE);
	exec->envi = ft_envi_update_value("OLDPWD", old_pwd, 0, exec->envi);
	if (exec->envi == FAIL)
		return (EXIT_FAILURE);
	ft_free_strs(exec->env);
	exec->env = ft_envi_to_env(exec->envi);
	if (exec->env == FAIL)
		return (EXIT_FAILURE);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
