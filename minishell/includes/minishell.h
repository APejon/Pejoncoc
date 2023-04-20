/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:59:56 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/20 13:15:12 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITE		"\033[0m"
# define YELLOW		"\033[1;33m"
# define GREEN		"\033[1;32m"
# define BLUE		"\033[1;34m"
# define CYAN		"\033[1;36m"
# define RED		"\033[1;31m"
# define PURPLE		"\033[0;35m"

/*-------- libft --------*/
# include "../libft/includes/libft.h"

/*-------- printf --------*/
# include "../libft/includes/pt_printf.h"

/*-------- get_next_line --------*/
# include "../libft/includes/get_next_line.h"

/*write, read, close, access, pipe, dup, dup2, execve and fork */
# include <unistd.h>

/*-------- boolean --------*/
# include <stdbool.h>

/*-------- perror --------*/
# include <stdio.h>

/*-------- malloc, free and exit --------*/
# include <stdlib.h>

/*-------- strerror --------*/
# include <string.h>

/*-------- readline --------*/
# include <readline/readline.h>
# include <readline/history.h>

/*-------- errno --------*/
# include <sys/errno.h>

/*-------- open and unlink --------*/
# include <fcntl.h>

/*-------- waitpid --------*/
# include <sys/wait.h>

/*-------- signal --------*/
# include <signal.h>

/*-------- stat --------*/
# include <sys/stat.h>

/*-------- Header files made --------*/
# include "structs.h"
# include "builtins.h"
# include "environment.h"
# include "execution.h"
# include "parsing.h"
# include "signals.h"

/*-------- Global variable --------*/
int		g_stdin;

/*-------- msh_error.c --------*/
void	msh_conditional_close(t_command *command);
void	msh_free_to_exit(t_shell *shell);
void	msh_complete_close(t_shell *shell, t_command *command);
void	msh_file_error(t_shell *shell, t_direct *redir, char *err_message,
			int exit);
void	msh_print_error(t_shell *shell, t_command *command, char *err_message,
			int exit);

/*-------- msh_free.c --------*/
void	msh_array_free(t_shell *shell, int i);
void	msh_complete_free(t_shell *shell);
void	msh_free_node(t_env *node);
void	msh_free_list(t_env **list);
void	msh_free(void *memory);

#endif