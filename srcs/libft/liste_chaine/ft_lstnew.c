/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:59:40 by pjay              #+#    #+#             */
/*   Updated: 2023/02/02 10:56:44 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*contenu;

	contenu = malloc(sizeof(*contenu));
	if (!contenu)
		return (NULL);
	contenu->content = content;
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
