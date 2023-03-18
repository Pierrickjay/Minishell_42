/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:40:03 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:28:45 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	ft_cd_update_oldpwd(t_shell *shell, char *oldpwd)
{
	char	*str;
	t_envi	*new;

	if (ft_getenvi("OLDPWD", shell->envi))
	{
		ft_envi_update_value("OLDPWD", oldpwd, NORMAL, shell->envi);
		free(oldpwd);
	}
	else
	{
		str = ft_strdup("OLDPWD");
		if (!str)
			return (free(oldpwd), ft_msg(NULL, "cd", errno, NULL), 1);
		new = ft_envi_new(str, oldpwd, NORMAL);
		if (!new)
			return (free(oldpwd), ft_msg(NULL, "cd", errno, NULL), 1);
		ft_envi_add_back(&shell->envi, new);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd_update_pwd(t_shell *shell, char *pwd)
{
	char	*str;
	t_envi	*new;

	if (ft_getenvi("PWD", shell->envi))
	{
		ft_envi_update_value("PWD", pwd, NORMAL, shell->envi);
		free(pwd);
	}
	else
	{
		str = ft_strdup("PWD");
		if (!str)
			return (free(pwd), ft_msg(NULL, "cd", errno, NULL), 1);
		new = ft_envi_new(str, pwd, NORMAL);
		if (!new)
			return (free(pwd), ft_msg(NULL, "cd", errno, NULL), 1);
		ft_envi_add_back(&shell->envi, new);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd_home(t_shell *shell)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ft_msg(NULL, "ft_cd (28)", errno, NULL), 1);
	if (!ft_getenvi("HOME", shell->envi))
		return (free(oldpwd), ft_msg_builtins("cd", NULL, HOME), 1);
	if (chdir(ft_getenvi("HOME", shell->envi)))
		return (free(oldpwd), ft_msg(NULL, "cd", errno, NULL), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), ft_msg(NULL, "cd", errno, NULL), 1);
	if (ft_cd_update_oldpwd(shell, oldpwd))
		return (free(pwd), EXIT_FAILURE);
	if (ft_cd_update_pwd(shell, pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd_back(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	if (ft_getenvi("OLDPWD", shell->envi) == NULL)
		return (ft_msg_builtins("cd", NULL, OLDPWD), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ft_msg(NULL, "cd", errno, NULL), 1);
	if (chdir(ft_getenvi("OLDPWD", shell->envi)))
		return (ft_msg(NULL, "cd", errno, NULL), 1);
	ft_putendl_fd(oldpwd, STDOUT);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), ft_msg(NULL, "cd", errno, NULL), 1);
	if (ft_cd_update_oldpwd(shell, oldpwd))
		return (EXIT_FAILURE);
	if (ft_cd_update_pwd(shell, pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd_go_to(t_shell *shell, const char *arg)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ft_msg(NULL, "cd", errno, NULL), 1);
	if (chdir(arg))
		return (free(oldpwd), \
				ft_msg_builtins("cd", (char *)arg, strerror(errno)), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), ft_msg(NULL, "cd", errno, NULL), 1);
	if (ft_cd_update_oldpwd(shell, oldpwd))
		return (free(pwd), EXIT_FAILURE);
	if (ft_cd_update_pwd(shell, pwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
