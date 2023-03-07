/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:09:56 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 17:21:44 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// get the type of the variable
int	ft_get_type_var(int *prev)
{
	if (*prev == -1 || *prev == PIPE || *prev == FILES)
		return (CMD);
	return (ARG);
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

// update lst content to empty string
int	ft_update_lst(t_list *lst, t_list *to_join, int *prev)
{
	free(lst->content);
	lst->content = ft_lstjoin(to_join);
	if (!lst->content)
		return (EXIT_FAILURE);
	lst->type = ft_get_type_var(prev);
	return (EXIT_SUCCESS);
}

// get the number of variables in a string
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

char	*ft_check_vars(t_exec *exec, size_t size, t_list **to_join, char *vars)
{
	size_t	len;
	char	*add;
	size_t	i;

	i = 0;
	len = ft_strlen(vars);
	while (vars[0] == '$' && !ft_all_isalnum(&vars[1]) && len-- && i < size)
	{
		if (ft_strcmp(vars, "$?") == 0)
		{
			add = ft_itoa(exec->exit_code);
			if (!add)
				return (NULL);
			ft_lstadd_front(to_join, ft_lstnew(add, -1));
			ft_bzero(vars, ft_strlen(vars));
			break ;
		}
		add = ft_strdup(&vars[len]);
		if (!add)
			return (NULL);
		vars[len] = '\0';
		ft_lstadd_front(to_join, ft_lstnew(add, -1));
		i++;
	}
	return (vars);
}
