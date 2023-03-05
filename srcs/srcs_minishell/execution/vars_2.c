/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:09:56 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/05 12:46:23 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_get_type_var(int *prev)
{
	if (*prev == -1 || *prev == PIPE || *prev == FILES)
		return (CMD);
	*prev = ARG;
	return (ARG);
}

int	ft_set_exit_code(t_list *lst, int exit_code, int prev, int mode_free)
{
	char	*str;

	str = ft_itoa(exit_code);
	if (!str)
		return (EXIT_FAILURE);
	if (mode_free)
		free(lst->content);
	lst->content = str;
	lst->type = ft_get_type_var(&prev);
	return (EXIT_SUCCESS);
}

int	ft_update_lst(t_list **lst)
{
	ft_free((void **)&(*lst)->content);
	(*lst)->type = ARG;
	(*lst)->content = ft_strdup("\0");
	if (!(*lst)->content)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

size_t	ft_nb_var(char *str)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nb++;
		i++;
	}
	return (nb);
}
