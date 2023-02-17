/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/17 10:12:10 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	*create_space(void)
{
	char	*newsplit;

	newsplit = malloc(sizeof(char) * 2);
	if (!newsplit)
		return (NULL);
	newsplit[0] = ' ';
	newsplit[1] = '\0';
	return (newsplit);
}

void	show_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d = %s\n", i, list->content);
		printf("Enum type = %d\n", list->type);
		i++;
		list = list->next;
	}
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
