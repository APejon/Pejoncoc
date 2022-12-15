/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:59:56 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/15 18:43:07 by cafriem          ###   ########.fr       */
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
# include "execution.h"
# include "parsing.h"
# include "signals.h"
# include "tokens.h"

/*-------- libft --------*/
# include "libft.h"

typedef enum e_philo_state
{
	DEFAULT,
	RE_INPUT,
	RE_OUTPUT,
	HERE_DOC,
	APPEND
}	t_state;

typedef struct s_shell
{
	char				*current_line;
	char				*line;
	char				**o_env;
	char				**u_env;
	int					exit_code;
	struct s_command	*command;
}	t_shell;

typedef struct s_command
{
	char	*command;
	char	*flag;
	char	*target;
	t_state	direct;
}	t_command;

/*-------- utils.c --------*/
void	msh_free(void *memory);
char	*msh_find_env(char **envp, char *line);

#endif