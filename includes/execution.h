/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:30:46 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/22 09:43:52 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
/*
 * readline, rl_clear_history, rl_on_new_line,
 * rl_replace_line, rl_redisplay, add_history,
 * printf, malloc, free, write, access, open, read,
 * close, fork, wait, waitpid, wait3, wait4, signal,
 * sigaction, sigemptyset, sigaddset, kill, exit,
 * getcwd, chdir, stat, lstat, fstat, unlink, execve,
 * dup, dup2, pipe, opendir, readdir, closedir,
 * strerror, perror, isatty, ttyname, ttyslot, ioctl,
 * getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
 * tgetnum, tgetstr, tgoto, tputs
*/
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <curses.h>
# include <string.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

//macros
# define PROMPT "minishell$ "
# define PATH "Path failed"
# define MALLOC "Malloc failed"
# define SYNTAX "Syntax error"
# define FORK "Fork failed"
# define EXEC "Execve failed"
# define PIPES "Pipe failed"
# define DUP "Dup failed"

//return values
# define FAIL (void *)-1
# define SUCCESS 0
# define FAILURE -1

typedef enum e_fd
{
	STDIN,
	STDOUT,
	STDERR
}	t_fd;

typedef enum e_redir
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir;

//struct for the shell
typedef struct s_vars
{
	t_list	*lst;
	char	**env;
	size_t	i;
	size_t	nb;
	size_t	nb_redir;
	size_t	nb_redir_type[4];
	t_list	*redir;
	pid_t	*pid;
	int		**pipes;
	char	***args;
	int		status;
}	t_vars;

//vars.c
t_vars	*ft_init_vars(t_list *lst, char **env);
void	*ft_init_vars_bis(t_vars *vars, t_list *lst);
pid_t	*ft_init_pid(t_vars *vars);
int		**ft_init_pipes(t_vars *vars);
char	***ft_init_args(t_vars *vars, t_list *lst);
size_t	ft_nb_cmds(t_list *lst);
size_t	ft_nb_redir(t_list *lst);
t_redir	ft_redir_type(char *str);
t_list	*ft_lst_redir(t_list *lst);
void	ft_nb_redir_type(t_list *redir, t_vars *vars);

//free.c
void	ft_free(void **ptr);
void	ft_free_strs(char **strs);
void	ft_free_lst(t_list *lst);
void	ft_free_pipes(int **pipes, size_t nb);
void	ft_free_args(char ***args, size_t nb);
void	ft_free_vars(t_vars *vars);

//here_doc.c
int		ft_here_doc(char *end);

//open.c
int		ft_open(char *name, t_redir type);
int		ft_open_infiles(t_list *redir, int infile, int here_doc, int nb);
int		ft_open_infiles_here_doc(t_list *redir);
int		ft_open_outfiles(t_list *redir, int outfile, int append);

//close.c
void	ft_close_pipes(int **pipes, size_t nb);

//path
char	**ft_get_path(void);
char	*ft_access(char *cmd, char **path);

//exec
int		main_exec(t_list *lst, char **env);
int		ft_exec_parent(t_vars *vars);
int		ft_exec_pipe_parent(t_vars *vars);
int		ft_exec_redir_parent(t_vars *vars);
int		ft_exec_pipe_redir_parent(t_vars *vars);

//child
void	ft_exec_child(t_vars *vars);
void	ft_exec_pipe_child(t_vars *vars);
void	ft_exec_redir_child(t_vars *vars);
void	ft_exec_pipe_file_child(t_vars *vars);

//args
size_t	ft_args_size(t_list *lst);
char	**ft_lst_to_args(t_list *lst);

//builtins
int		ft_builtins(t_vars *vars);
int		ft_echo(t_vars *vars); //not ok
int		ft_cd(t_vars *vars); //not ok
int		ft_pwd(t_vars *vars); //not ok
int		ft_export(t_vars *vars); //not ok
int		ft_unset(t_vars *vars); //not ok
int		ft_env(t_vars *vars); //not ok
int		ft_exit(t_vars *vars); //not ok

#endif
