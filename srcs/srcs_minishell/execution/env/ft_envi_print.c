/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envi_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:41:02 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/18 19:28:23 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	swap_envi_nodes(t_envi *a, t_envi *b)
{
	char	*temp_key;
	char	*temp_value;
	int		temp_type;

	temp_value = a->value;
	temp_key = a->key;
	temp_type = a->type;
	a->key = b->key;
	a->value = b->value;
	a->type = b->type;
	b->key = temp_key;
	b->value = temp_value;
	b->type = temp_type;
}

void	sort_envi_list(t_envi **head)
{
	int		swapped;
	t_envi	*ptr1;
	t_envi	*lptr;

	lptr = NULL;
	swapped = 1;
	if (*head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_envi_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

// print the list
void	ft_envi_print(t_shell *shell, t_envi *envi)
{
	t_envi	*swapped;
	t_envi	*head;

	swapped = ft_dup_envi(envi);
	if (swapped == NULL)
		return ;
	sort_envi_list(&swapped);
	head = swapped;
	while (swapped)
	{
		if (ft_putstr_fd("declare -x ", STDOUT) == FAILURE || \
			ft_putstr_fd(swapped->key, STDOUT) == FAILURE)
			return (ft_msg(shell, EXPORT_ERROR, errno, &exit));
		if (swapped->type == NORMAL)
		{
			if (ft_putstr_fd("=\"", STDOUT) == FAILURE || \
				ft_putstr_fd(swapped->value, STDOUT) == FAILURE || \
				ft_putstr_fd("\"", STDOUT) == FAILURE)
				return (ft_msg(shell, EXPORT_ERROR, errno, &exit));
		}
		if (ft_putchar_fd('\n', STDOUT) == FAILURE)
			return (ft_msg(shell, EXPORT_ERROR, errno, &exit));
		swapped = swapped->next;
	}
	ft_free_envi(head);
}
