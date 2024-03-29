/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:49:19 by pjay              #+#    #+#             */
/*   Updated: 2023/03/18 18:57:04 by obouhlel         ###   ########.fr       */
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

# define SYNTAXE_ERROR "syntax error near unexpected token"

# define _COLOR_RED "\033[0;31m"
# define _COLOR_GREEN "\033[0;32m"
# define _COLOR_YELLOW "\033[0;33m"
# define _COLOR_BLUE "\033[0;34m"
# define _COLOR_MAGENTA "\033[0;35m"
# define _COLOR_CYAN "\033[0;36m"
# define _COLOR_WHITE "\033[0;37m"
# define _COLOR_RESET "\033[0m"

# define MINISHELL "\n\
███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      \n\
████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      \n\
██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      \n\
██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      \n\
██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ \n"

# define BY "version 2.0\t\t\t\t\tby pjay & obouhlel\n"

//pjay
# include "parsing.h"
//obouhlel
# include "execution.h"

#endif
