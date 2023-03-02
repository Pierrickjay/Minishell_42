/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:06:47 by obouhlel          #+#    #+#             */
/*   Updated: 2023/02/28 13:06:03 by obouhlel         ###   ########.fr       */
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
//pjay
# include "parsing.h"
//obouhlel
# include "execution.h"

#endif