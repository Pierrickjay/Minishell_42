/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:15 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/06 14:49:48 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Modif pour faire fonctionner le parsing le if*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_lst_print(t_list *lst, int endl)
{
	while (lst)
	{
		ft_putstr_fd(lst->content, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		lst = lst->next;
	}
	if (endl == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	delete_content(void *content)
{
	(void)content;
	content = NULL;
}
