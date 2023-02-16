/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:44:51 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/15 13:13:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**ft_get_path(void)
{
	char	**path;
	char	*tmp;

	tmp = getenv("PATH");
	if (!tmp)
		return (ft_putendl_fd(PATH, STDERR), NULL);
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
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
		if (access(tmp, X_OK) != -1)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}
