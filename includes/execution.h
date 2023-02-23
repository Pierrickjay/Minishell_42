/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:30:46 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/23 14:38:53 by obouhlel         ###   ########.fr       */
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

//env
typedef struct s_envi
{
	char			*key;
	char			*value;
	struct s_envi	*next;
}	t_envi;

//struct for the shell
typedef struct s_exec
{
	t_list	*lst;
	char	**env;
	t_envi	*envi;
	size_t	i;
	size_t	nb;
	size_t	nb_redir;
	size_t	nb_redir_type[4];
	t_list	*redir;
	pid_t	*pid;
	int		**pipes;
	char	***args;
	int		status;
}	t_exec;

/***********************************EXECUTION**********************************/
//parent
t_exec	*main_exec(t_list *lst, char **env);
int		ft_exec_parent(t_exec *exec);
int		ft_exec_pipe_parent(t_exec *exec);
int		ft_exec_redir_parent(t_exec *exec);
int		ft_exec_pipe_redir_parent(t_exec *exec);

//child
//child_1.c
void	ft_exec_child(t_exec *exec);
void	ft_exec_pipe_child(t_exec *exec);
void	ft_exec_redir_child(t_exec *exec);
//child_2.c
void	ft_exec_pipe_file_child(t_exec *exec);

//exec.c
//exec_1.c
t_exec	*ft_init_exec(t_list *lst, char **env);
void	*ft_init_exec_bis(t_exec *exec, t_list *lst);
pid_t	*ft_init_pid(t_exec *exec);
int		**ft_init_pipes(t_exec *exec);
char	***ft_init_args(t_exec *exec, t_list *lst);
//exec_2.c
size_t	ft_nb_cmds(t_list *lst);
size_t	ft_nb_redir(t_list *lst);
t_redir	ft_redir_type(char *str);
t_list	*ft_lst_redir(t_list *lst);
void	ft_nb_redir_type(t_list *redir, t_exec *exec);

//args.c
size_t	ft_args_size(t_list *lst);
char	**ft_lst_to_args(t_list *lst);

//path.c
char	**ft_get_path(void);
char	*ft_access(char *cmd, char **path);

//vars.c
void	*ft_get_vars(t_exec *exec);
/******************************************************************************/

/************************************UTILS*************************************/
//close.c
void	ft_close_pipes(int **pipes, size_t nb);

//dup_env.c
char	**ft_dup_env(char **env);

//free.c
//free_1.c
void	ft_free_strs(char **strs);
void	ft_free_lst(t_list *lst);
void	ft_free_pipes(int **pipes, size_t nb);
void	ft_free_args(char ***args, size_t nb);
void	ft_free_redir(t_list *lst);
//free_2.c
void	ft_free(void **ptr);
void	ft_free_strs_n(char **strs, int n);
void	ft_free_envi(t_envi *envi);
void	ft_free_exec(t_exec *exec);
//free_3.c
void	ft_free_child(t_exec *exec, char **path, char *cmd);

//setenv.c
int		ft_setenv(const char *name, const char *value, int overwrite);

//here_doc.c
int		ft_here_doc(char *end);

//open.c
int		ft_open(char *name, t_redir type);
int		ft_open_infiles(t_list *redir, int infile, int here_doc, int nb);
int		ft_open_infiles_here_doc(t_list *redir);
int		ft_open_outfiles(t_list *redir, int outfile, int append);
/******************************************************************************/

/*************************************ENV**************************************/
t_envi	*ft_envi_new(char *key, char *value);
void	ft_envi_add_back(t_envi **envi, t_envi *new);
size_t	ft_envi_size(t_envi *envi);
t_envi	*ft_envi_last(t_envi *envi);
char	**ft_envi_to_env(t_envi *envi);
t_envi	*ft_env_to_envi(char **env);
/******************************************************************************/

/***********************************BUILTINS***********************************/
int		ft_builtins(t_exec *exec);
int		ft_echo(t_exec	*exec);
int		ft_pwd(t_exec *exec);
int		ft_cd(t_exec *exec); //not ok
int		ft_env(t_exec *exec);
int		ft_export(t_exec *exec); //not ok
int		ft_unset(t_exec *exec); //not ok
/******************************************************************************/

#endif
