/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:30:46 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/22 09:55:04 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// other includes
# include "minishell.h"
# include "parsing.h"

//return values
# define FAIL (void *)-1
# define SUCCESS 0
# define FAILURE -1
# define TRUE 1
# define FALSE 0

//error messages
# define EXPORT_ERROR "export: write error"
# define ECHO_ERROR "echo: write error"
# define PERM "Permission denied"
# define NOENT "No such file or directory"
# define HOME "HOME not set"
# define OLDPWD "OLDPWD not set"
# define IDENT "not a valid identifier"
# define TOOMANY "too many arguments"

// fd standard
typedef enum e_fd
{
	STDIN,
	STDOUT,
	STDERR
}	t_fd;

// infile or outfile
typedef enum e_mode
{
	IN,
	OUT,
}	t_mode;

// type of redirection
typedef enum e_redir
{
	INFILE,
	TRUNC,
	APPEND
}	t_redir;

// error codes
typedef enum e_error
{
	MA = -1,
	SY = -2,
	PA = -3,
	CM = -4,
	EX = -5
}	t_error;

// type of export in env or not
enum e_export
{
	NORMAL,
	NO_VALUE
};

// envi it's a list of environnement variables
typedef struct s_envi
{
	char			*key;
	char			*value;
	int				type;
	struct s_envi	*next;
}	t_envi;

// struct for the heredoc for the free more easily
// and give the arguments to the function more easily
typedef struct s_heredoc
{
	t_list	*lst;
	t_envi	*envi;
	int		*count_line;
	int		*exit_code;
}	t_heredoc;

// struct for the shell
typedef struct s_shell
{
	t_list	*lst;
	char	**env;
	t_envi	*envi;
	int		id_child;
	int		no_cmd;
	int		nb_cmd;
	int		nb_redir;
	int		*infile;
	int		*outfile;
	t_list	**redir;
	pid_t	*pid;
	int		**pipes;
	char	***args;
	int		status;
	int		*count_line;
	int		*exit_code;
}	t_shell;

/************************************STRUCT************************************/
//struct.c
//shell_1.c
t_shell	*init_shell(t_list *lst, t_envi *envi, int *countline, int *exitcode);
int		init_shell_bis(t_shell *shell, t_list *lst);
pid_t	*ft_init_pid(t_shell *shell);
int		**ft_init_pipes(t_shell *shell);
char	***ft_init_args(t_shell *shell, t_list *lst);
//shell_2.c
int		ft_lst_redir_malloc(t_shell *shell, t_list *lst);
int		ft_set_redir(t_shell *shell, t_list *lst, t_list **redir);
void	ft_check_next(t_shell *shell, t_list *lst, int type[2], int *i);
int		ft_set_file(int type[2], int mode);
int		ft_redir_type(char *str, int type[2]);
//shell_3.c
size_t	ft_nb_cmds(t_list *lst);
size_t	ft_nb_redir(t_list *lst);
int		ft_set_redir_no_cmd(t_shell *shell, t_list *lst, t_list **redir);
/******************************************************************************/

/***********************************EXECUTION**********************************/
//parent
//parent_1.c
t_envi	*main_exec(t_list *lst, t_envi *envi, int *count_line, int *exit_code);
void	deal_w_return_pid(int status);
int		ft_parent_bis(t_shell *shell, t_envi *envp);
void	ft_update_shlvl(t_shell *shell);
void	ft_exit_code(t_shell *shell);
//parent_2.c
int		ft_shell_parent_no_cmd(t_shell *shell);
int		ft_shell_parent(t_shell *shell);
int		ft_shell_pipe_parent(t_shell *shell);
int		ft_shell_redir_parent(t_shell *shell);
int		ft_shell_pipe_redir_parent(t_shell *shell);

//child
//child_1.c
void	ft_shell_child_no_cmd(t_shell *shell);
void	ft_shell_child(t_shell *shell);
void	ft_shell_child_bis(t_shell *shell, const int n);
void	ft_shell_pipe_child(t_shell *shell);
void	ft_shell_redir_child(t_shell *shell);
//child_2.c
void	ft_shell_pipe_file_child(t_shell *shell);

//expend_1.c
int		ft_lst_expend(t_envi *envi, t_list *lst, int exit_code);
char	*ft_expend(t_envi *envi, char *content, int exit_code);
char	*ft_expend_bis(t_envi *envi, char *vars, int exit_code);
char	*ft_expend_join(t_envi *envi, t_list **to_join, char *var);
int		ft_expend_exit_code(char *var, t_list **to_join, int exit_code);
//expend_2.c
size_t	ft_nb_var(char *str);
int		ft_var_special(char c);
char	*ft_content_update(char *str);
char	*ft_check_envi(char *key, t_envi *envi);
int		find_dollad_pos(char *str);
/******************************************************************************/

/************************************UTILS*************************************/
//args.c
size_t	ft_args_size(t_list *lst);
int		ft_space_in_cmd(t_list *lst);
int		ft_strlen_space(char *str);
int		ft_split_at_space_cmd(t_list *lst, char **args, size_t *i);
char	**ft_lst_to_args(t_list *lst);

//close.c
void	ft_close_pipes(int **pipes, size_t nb);
void	ft_close(int *fd);

//free.c
//free_1.c
void	ft_free_strs(char **strs);
void	ft_free_lst(t_list *lst);
void	ft_free_pipes(int **pipes, size_t nb);
void	ft_free_args(char ***args, size_t nb);
void	ft_free_redir(t_list **lst, int nb);
//free_2.c
void	ft_free(void **ptr);
void	ft_free_strs_n(char **strs, int n);
void	ft_free_envi(t_envi *envi);
void	ft_free_shell(t_shell *shell);
//free_3.c
void	ft_free_child(t_shell *shell, char **path, char *cmd);
void	ft_free_envi_delone(t_envi *envi);
void	ft_free_lst_delone(t_list **lst, t_list *previous);
void	ft_free_heredoc(t_heredoc *heredoc, char *limiter, char *line, int fd);

//ft_msg.c
void	ft_msg(t_shell *shell, char *str, int value, void (*f)(int));
void	ft_msg_builtins(char *cmd, char *arg, char *str);
void	ft_msg_malloc(char *files);

//heredoc_1.c
int		run_heredoc(t_list *lst, t_envi *envi, int *countline, int *exitcode);
int		run_heredoc_bis(t_heredoc *heredoc, t_list *lst);
void	ft_unlink(t_list *lst);
//heredoc_2.c
void	ft_heredoc(char *limiter, char *name_file, t_heredoc *heredoc);
char	*ft_get_line(t_heredoc *heredoc, char *limiter, int fd);
void	finish_here_doc(int fd, char *limiter, char *line, t_heredoc *heredoc);
void	to_print_error(t_heredoc *heredoc, char *limiter, int fd);
void	ft_msg_heredoc(t_heredoc *heredoc, char *str, int n, void (*f)(int));

//open.c
int		ft_open(char *name, t_redir type);
int		ft_open_infiles(t_shell *shell, t_list *redir);
int		ft_open_outfiles(t_shell *shell, t_list *redir);

//path.c
char	**ft_get_path(t_shell *shell);
char	*ft_access(char *cmd, char **path);

//random.c
char	*ft_random(int nb_char);

//utils.c
int		ft_nb_args_child(char **args);
int		ft_all_isalnum(char *str);
int		ft_check_last_char(char *str, char c);
t_envi	*ft_dup_envi(t_envi *envi);
int		ft_all_isalnum_len(char *str, int len);
/******************************************************************************/

/*************************************ENV**************************************/
t_envi	*ft_envi_new(char *key, char *value, int type);
void	ft_envi_add_back(t_envi **envi, t_envi *new);
size_t	ft_envi_size(t_envi *envi);
t_envi	*ft_envi_last(t_envi *envi);
char	**ft_envi_to_env(t_envi *envi);
t_envi	*ft_env_to_envi(char **env);
char	*ft_get_key(char *env);
char	*ft_get_value(char *env);
char	*ft_getenvi(char *name, t_envi *envi);
t_envi	*ft_envi_update_value(char *key, char *value, int type, t_envi *envi);
void	ft_envi_print(t_shell *shell, t_envi *envi);
t_envi	*ft_envi_null(t_envi *envi);
/******************************************************************************/

/***********************************BUILTINS***********************************/
//for echo, env, pwd, and export with no arg
int		builtins_in_child(t_shell *shell);
//for export, unset, cd
int		builtins_in_parent(t_shell *shell);
//echo
int		ft_echo(t_shell	*shell);
//pwd
int		ft_pwd(t_shell *shell);
//cd
int		ft_cd(t_shell *shell);
//cd_bis.c
int		ft_cd_update_oldpwd(t_shell *shell, char *oldpwd);
int		ft_cd_update_pwd(t_shell *shell, char *pwd);
int		ft_cd_home(t_shell *shell);
int		ft_cd_back(t_shell *shell);
int		ft_cd_go_to(t_shell *shell, const char *arg);
//env
int		ft_env(t_shell *shell);
//export
int		ft_export(t_shell *shell);
//unset
int		ft_unset(t_shell *shell);
/******************************************************************************/

#endif
