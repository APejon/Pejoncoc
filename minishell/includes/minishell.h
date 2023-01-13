/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:59:56 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/13 12:49:58 by cafriem          ###   ########.fr       */
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

/*-------- Header files made --------*/
# include "structs.h"
# include "builtins.h"
# include "environment.h"
# include "execution.h"
# include "parsing.h"
# include "signals.h"

/*-------- libft --------*/
# include "libft.h"

/*-------- printf --------*/
# include "pt_printf.h"

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

// # include <string.h>
// # include <sys/wait.h>
// # include <fcntl.h>
// # include <sys/stat.h>
// # include <signal.h>

/*-------- msh_utils.c --------*/
void	msh_print_error(t_shell *shell, t_command *command, char *err_message,
			int exit);
void	msh_print_flerror(t_shell *shell, t_command *command, char *rec_flags);
void	msh_free_node(t_env *node);
void	msh_free_list(t_env **list);
void	msh_free(void *memory);

#endif