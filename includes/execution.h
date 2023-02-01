/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:30:46 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/01 11:47:02 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

void	ft_echo_exec(t_list *cmd);
void	ft_lst_print(t_list *lst, int endl);
int		ft_strcmp(const char *s1, const char *s2);
void	delete_content(void *content);

#endif