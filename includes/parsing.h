/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:29:52 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/01 15:43:01 by pjay             ###   ########.fr       */
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
int		count_quote(char **str);
char	*make_it_clean(char *str);
char	*ft_strdup_modif(char *s, int to_free);
char	**split_parsing(char const *s, char c);
size_t	split_w_double(const char *s);
size_t	split_w_single(const char *s);
int		count_word(const char *s, bool single);
char	*remove_double(char *str);
char	*remove_single(char *str);
int		check_order_quote(char *str);
#endif
