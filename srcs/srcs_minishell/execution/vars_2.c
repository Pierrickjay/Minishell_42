/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:09:56 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/08 12:03:16 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_check_var_3(char *var, t_list **to_join, int exit_code)
{
	char	*add;

	add = NULL;
	if (!ft_strcmp("$?", var))
	{
		add = ft_itoa(exit_code);
		if (!add)
			return (EXIT_FAILURE);
		ft_lstadd_front(to_join, ft_lstnew(add, -1));
	}
	ft_bzero(var, ft_strlen(var));
	return (EXIT_SUCCESS);
}

// update the string when we have a lot dorlars and add space before dolars
char	*ft_content_update(char *str)
{
	size_t	nb_dolars;
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new_str;

	nb_dolars = ft_nb_var(str);
	len = ft_strlen(str);
	new_str = ft_calloc((nb_dolars + len + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			new_str[j++] = ' ';
		new_str[j++] = str[i++];
	}
	ft_free((void **)&str);
	return (new_str);
}

char	**ft_lst_split_vars_bis(t_list *tmp)
{
	char	**strs;

	strs = ft_split(tmp->content, ' ');
	if (!strs)
		return (FAIL);
	free(tmp->content);
	tmp->content = strs[0];
	return (strs);
}

// split vars, when we have a lot espace, and we have one cmd, and opt or arg
int	ft_lst_split_vars(t_list *tmp)
{
	char	**strs;
	t_list	*new;
	t_list	*args;
	char	*str;
	int		i;

	if (tmp->content[0] == '\0')
		return (EXIT_SUCCESS);
	strs = ft_lst_split_vars_bis(tmp);
	if (strs == FAIL)
		return (EXIT_FAILURE);
	args = NULL;
	i = 1;
	while (strs[i])
	{
		str = strs[i];
		new = ft_lstnew(str, ARG);
		if (!new)
			return (EXIT_FAILURE);
		ft_lstadd_back(&args, new);
		i++;
	}
	return (ft_lstadd(&tmp, args), free(strs), EXIT_SUCCESS);
}

