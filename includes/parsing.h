/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:29:52 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/07 16:35:30 by pjay             ###   ########.fr       */
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
# define MAIN 0
# define CHILD 2
# define PARENT 1
# define HEREDOC 3

typedef struct s_free
{
	char	**split;
}	t_free;

void	ft_main_parsing(void);
void	ft_main_parsing_utils(void);
int		create_siga(int mode);
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
char	*remove_double(char *str, int index);
char	*remove_single(char *str, int index);
int		check_order_quote(char *str);
void	free_all(char **split, char *save);
int		save_is_null(char *save, t_envi *envp);
void	ft_exit(t_list *list, t_envi *envp);
int		ft_check_list(t_list *list, t_free *to_free, char *save, t_envi *envp);
void	*free_inverse_split(char **split, int i);
int		count_quote_single(char *str);
void	*free_str_quote_error(char *str);
int		go_next_quote(char *str, int index, char c);
char	*new_string(char *str);
int		to_go_next_quote_double(char *str, char *new_str, int i, int j);
int		to_go_next_quote_single(char *str, char *new_str, int i, int j);
int		fill_string_double(char *new_str, char *str, char c);
int		fill_string_single(char *new_str, char *str, char c);
char	*separate_pipe(char *str);
int		check_arrow_pipe(t_list *lst);
void	ft_print_exeptected_token(char *str);
int		check_redir_nb(t_list *lst);
void	increment_fill(char *str, char *new_str, int *i, int j);
void	handler_quit(int signal);
#endif
