/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:30:46 by obouhlel          #+#    #+#             */
/*   Updated: 2023/03/10 18:06:41 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"
# include "parsing.h"

//error messages
# define EXPORT_ERROR "export: write error"
# define ECHO_ERROR "echo: write error"
# define PERM "Permission denied"
# define NOENT "No such file or directory"
# define HOME "HOME not set"
# define IDENT "not a valid identifier"

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
	INFILE,
	TRUNC,
	APPEND,
	HEREDOC
}	t_redir;

typedef enum e_error
{
	MA = -1,
	SY = -2,
	PA = -3,
	CM = -4,
	EX = -5
}	t_error;

enum e_export
{
	NORMAL,
	NO_VALUE
};

//env
typedef struct s_envi
{
	char			*key;
	char			*value;
	int				type;
	struct s_envi	*next;
}	t_envi;

//struct for the shell
typedef struct s_exec
{
	t_list	*lst;
	char	**env;
	t_envi	*envi;
	int		i;
	int		nb;
	int		nb_redir;
	int		nb_redir_type[4];
	t_list	*redir;
	pid_t	*pid;
	int		**pipes;
	char	***args;
	int		status;
	int		*count_line;
}	t_exec;

/***********************************EXECUTION**********************************/
//parent
//parent_1.c
t_envi	*main_exec(t_list *lst, t_envi *envi, int *count_line, int *exit_code);
void	deal_w_return_pid(int status);
int		ft_parent_bis(t_exec *exec, t_envi *envp);
void	ft_update_shlvl(t_exec *exec);
void	ft_exit_code(t_exec *exec);
//parent_2.c
int		ft_exec_parent_no_cmd(t_exec *exec);
int		ft_exec_parent(t_exec *exec);
int		ft_exec_pipe_parent(t_exec *exec);
int		ft_exec_redir_parent(t_exec *exec);
int		ft_exec_pipe_redir_parent(t_exec *exec);

//child
//child_1.c
void	ft_exec_child(t_exec *exec);
void	ft_exec_child_bis(t_exec *exec, const int n);
void	ft_exec_pipe_child(t_exec *exec);
void	ft_exec_redir_child(t_exec *exec);
void	ft_exec_redir_child_bis(t_exec *exec, int fd_in, int fd_out);
//child_2.c
void	ft_exec_pipe_file_child(t_exec *exec);
void	ft_exec_child_no_cmd(t_exec *exec);

//exec.c
//exec_1.c
t_exec	*ft_init_exec(t_list *lst, t_envi *envi, int *count_line);
int		ft_init_exec_bis(t_exec *exec, t_list *lst);
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
char	**ft_get_path(t_exec *exec);
char	*ft_access(char *cmd, char **path);

//vars_1.c
int		ft_get_vars(t_envi *envi, t_list *lst, int exit_code);
int		ft_only_one_var(t_envi *envi, t_list *lst, int prev);
int		ft_update_str_var(t_envi *envi, t_list *lst, int prev, int ec);
char	*ft_check_var_1(t_envi *envi, char *vars, int ec, size_t size);
char	*ft_check_var_2(t_envi *envi, size_t size, t_list **to_join, char *var);
//vars_2.c
int		ft_check_var_3(char *var, t_list **to_join, int exit_code);
int		ft_lst_split_vars(t_list *tmp);
char	*ft_content_update(char *str);
char	*ft_check_envi(char *key, t_envi *envi);
//vars_3.c
size_t	ft_nb_var(char *str);
int		ft_var_special(char c);
int		ft_get_type_var(int *prev);
int		ft_update_lst(t_list *lst, t_list *to_join, int *prev);
int		ft_set_exit_code(t_list *lst, int exit_code, int prev, int mode_free);
/******************************************************************************/

/************************************UTILS*************************************/
//close.c
void	ft_close_pipes(int **pipes, size_t nb);
void	ft_close(int *fd);

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
void	ft_free_envi_delone(t_envi *envi);

//ft_msg.c
void	ft_msg(t_exec *exec, char *str, int value, void (*f)(int));
void	ft_msg_builtins(char *cmd, char *arg, char *str);
void	ft_msg_malloc(char *files);

//here_doc.c
int		ft_here_doc(char *end, int *count_line, t_exec *exec);

//open.c
int		ft_open(char *name, t_redir type, int *count_line, t_exec *exec);
int		ft_open_infiles(t_list *redir, int nb, int *count_line, t_exec *exec);
int		ft_open_infiles_here_doc(t_list *redir, int *count_line, t_exec *exec);
int		ft_open_outfiles(t_list *redir, int *count_line, t_exec *exec);

//utils.c
int		ft_nb_args_child(char **args);
int		ft_all_isalnum(char *str);
int		ft_check_last_char(char *str, char c);
t_envi	*ft_dup_envi(t_envi *envi);
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
void	ft_envi_print(t_exec *exec, t_envi *envi);
/******************************************************************************/

/***********************************BUILTINS***********************************/
//for echo, env, pwd
int		ft_is_builtins(t_exec *exec);
//for export, unset, cd
int		ft_builtins(t_exec *exec);
//echo
int		ft_echo(t_exec	*exec);
//pwd
int		ft_pwd(t_exec *exec);
//cd
int		ft_cd(t_exec *exec);
int		ft_cd_1(t_exec *exec, char *pwd);
//env
int		ft_env(t_exec *exec);
//export
int		ft_export(t_exec *exec);
//unset
t_envi	*ft_unset_bis(const char *name, t_envi *envi);
int		ft_unset(t_exec *exec);
/******************************************************************************/

#endif
