/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:20 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/16 11:11:18 by pjay             ###   ########.fr       */
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

int		fill_it(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (0);
	return (1);

}

void	show_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d = %s\n",i, list->content);
		printf("Enum type = %d\n", list->type);
		i++;
		list = list->next;
	}
}

void	fill_enum(t_list *lst)
{
	int i;

	i = 0;
	while (lst->next)
	{
		if (fill_it(lst->content) == 0)
			lst->type = 0;
		else
			lst->type = -1;
		lst = lst->next;
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

