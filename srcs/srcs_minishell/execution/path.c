/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:44:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 13:05:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**ft_get_path(t_exec *exec)
{
	char	**path;
	char	*tmp;

	tmp = ft_getenvi("PATH", exec->envi);
	if (!tmp)
		return (ft_msg(exec, NULL, PA, &exit), NULL);
	path = ft_split(tmp, ':');
	if (!path)
		return (ft_msg(exec, NULL, MA, &exit), NULL);
	return (path);
}

char	*ft_access(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!tmp)
			return (NULL);
		errno = 0;
		if (access(tmp, X_OK) != -1)
			return (tmp);
		free(tmp);
		i++;
	}
	return (FAIL);
}
