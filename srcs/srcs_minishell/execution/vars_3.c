/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:10:48 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/09 09:36:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// count the nb or dolars in the string
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

//vars no print and not use for your minishell
int	ft_var_special(char c)
{
	if (ft_isdigit(c) || c == '?' || c == '!' || c == '@' || c == '#' \
		|| c == '&' || c == '\0' || c == '=' || c == '+' || c == '-' )
		return (true);
	return (false);
}

// get the type of the variable
int	ft_get_type_var(int *prev)
{
	if (*prev == -1 || *prev == PIPE || *prev == FILES)
		return (CMD);
	return (ARG);
}

// change the string and put a new string with list to_join
int	ft_update_lst(t_list *lst, t_list *to_join, int *prev)
{
	free(lst->content);
	lst->content = ft_lstjoin(to_join);
	if (!lst->content)
		return (EXIT_FAILURE);
	lst->type = ft_get_type_var(prev);
	return (EXIT_SUCCESS);
}

// set the exit code when $? is used
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
