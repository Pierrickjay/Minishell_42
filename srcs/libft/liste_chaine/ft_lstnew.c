/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:59:40 by pjay              #+#    #+#             */
/*   Updated: 2023/03/09 11:43:09 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

t_list	*ft_lstnew(char *content, int type)
{
	t_list	*contenu;

	contenu = ft_calloc(sizeof(*contenu), 1);
	if (!contenu)
		return (NULL);
	contenu->content = content;
	contenu->type = type;
	contenu->next = NULL;
	return (contenu);
}

t_list	*ft_lstnew_spe(char *content, int type, bool expend)
{
	t_list	*contenu;

	contenu = ft_calloc(sizeof(*contenu), 1);
	if (!contenu)
		return (NULL);
	contenu->not_expend = expend;
	contenu->content = content;
	contenu->type = type;
	contenu->next = NULL;
	return (contenu);
}

/*int main()
{
	t_list *newlist = NULL;

	ft_lstadd_front(&newlist, ft_lstnew((void*)"180\n"));
	printf("%s", newlist->content);
	ft_lstadd_front(&newlist, ft_lstnew((void*)8));
	printf("%d", newlist->next = newlist->content);
	ft_lstadd_front(&newlist, ft_lstnew((void*)"180\n"));
	printf("%s", newlist->next = newlist->content);
}*/
