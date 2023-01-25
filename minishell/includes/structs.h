/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:41:52 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/25 19:39:56 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_mini_state
{
	RE_INPUT,
	RE_OUTPUT,
	APPEND,
	HERE_DOC
}	t_state;

typedef struct s_shell
{
	char				*current_line;
	char				*line;
	char				*oldpwd;
	int					exit_code;
	int					nohd;
	struct s_env		*env;
	struct s_env		*dec_env;
	struct s_command	**command;
}	t_shell;

typedef struct s_env
{
	char				*variable;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_command
{
	char				**cmd_args;
	t_direct			**redir;
}	t_command;

typedef struct s_direct
{
	char				*file;
	char				*hd_content;
	t_state				direct;
}	t_direct;

#endif