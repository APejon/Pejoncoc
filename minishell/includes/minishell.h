/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:59:56 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/18 15:13:20 by amalbrei         ###   ########.fr       */
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
# include "builtins.h"
# include "environment.h"
# include "execution.h"
# include "parsing.h"
# include "signals.h"

/*-------- libft --------*/
# include "libft.h"

/*-------- boolean --------*/
# include <stdbool.h>

/*-------- perror --------*/
# include <stdio.h>

/*-------- malloc, free and exit --------*/
# include <stdlib.h>

/*-------- strerror --------*/
# include <string.h>

typedef enum e_mini_state
{
	DEFAULT,
	PIPE,
	RE_INPUT,
	RE_OUTPUT,
	HERE_DOC,
	APPEND
}	t_state;

typedef struct s_shell
{
	char				*current_line;
	char				*line;
	int					exit_code;
	struct s_env		*env;
	struct s_env		*dec_env;
	struct s_command	*command;
}	t_shell;

typedef struct s_env
{
	char				*variable;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_command
{
	char				*command;
	char				*flag;
	char				*target;
	t_state				direct;
}	t_command;

/*-------- msh_utils.c --------*/
void	msh_print_flerror(t_shell *shell, t_command *command, char *rec_flags);
void	msh_free(void *memory);

#endif