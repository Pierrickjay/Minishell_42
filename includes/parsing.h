/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:29:52 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/17 09:38:20 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "parsing.h"
# include "execution.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>


typedef struct s_free
{
	char	**split;
}	t_free;

void	ft_main_parsing(void);
void	ft_main_parsing_utils(void);
int		create_siga(void);
t_list	*ft_fill(char *str, t_free *to_free);
void	show_list(t_list *list);
void	block_signal(int signal);
void	unblock_signal(int signal);
void	free_split(char **split);
char	*create_space(void);
int		count_split(char **split);
void	fill_enum(t_list *lst);
char	**trim_all(char **split);
void	ft_set_type(t_list *lst);

#endif
