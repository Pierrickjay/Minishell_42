/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:23 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/01 15:32:57 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	show_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf(" %d = %s\n",i, (char *)list->content);
		i++;
		list = list->next;
	}
}


t_list	*ft_fill(char *str)
{
	char	**str_split;
	int		i;
	t_list	*list;
	t_list	*tmp;

	i = 1;
	list = ft_calloc(sizeof(*list), 1);
	if (!list)
		return (NULL);
	list->next = NULL;
	str_split = ft_split(str, ' ');
	list->content = str_split[0];
	while (str_split[i])
	{
		tmp = ft_lstnew(str_split[i]);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	printf("lst size = %d\n", ft_lstsize(list));
	show_list(list);
	return (list);
}

void	handler_end(int signal)
{
	if (signal == SIGINT)
		printf("\nServer Close\n");
	exit (0);
}

int main(void/*int ac, char **av*/)
{
	char	*save;
	t_list	*list;

	while (1)
	{
		save = readline("minishell>");
		printf("save = %s\n", save);
		list = ft_fill(save);
		free(save);
		free(list);
		signal(SIGINT, handler_end);
	}
	//printf("save = %s\n", save);
	return (0);
}
