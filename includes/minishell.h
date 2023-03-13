/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:49:19 by pjay              #+#    #+#             */
/*   Updated: 2023/03/13 20:19:14 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define PROMPT "minishell $> "

# define RED "\x1b[31m"
# define ORANGE "\x1b[38;5;208m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

# define MINISHELL "\n\
███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██          \n\
████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██          \n\
██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██          \n\
██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██          \n\
██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████     \n\
\n\
\t\t\t\t\t\t\x1b[34mby pjay & obouhlel\n"

# define SYNTAXE_ERROR "syntax error near unexpected token"

//pjay
# include "parsing.h"
//obouhlel
# include "execution.h"
# include "libft.h"

#endif
