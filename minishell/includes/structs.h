/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:41:52 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/22 13:54:31 by amalbrei         ###   ########.fr       */
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
	int					exit_code;
	int					nohd;
	char				*line;
	char				*oldpwd;
	struct s_env		*env;
	struct s_env		*dec_env;
	struct s_parser		*par;
	struct s_command	**command;
}	t_shell;

typedef struct s_env
{
	char				*variable;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_direct
{
	int					fd;
	char				*file;
	char				*hd_content;
	t_state				direct;
}	t_direct;

typedef struct s_command
{
	int					fd_in;
	int					fd_out;
	int					p_fd[2];
	pid_t				pid;
	char				**cmd_args;
	t_direct			**redir;
}	t_command;

typedef struct s_parser
{
	int		no_of_cmd_args;
	int		no_of_redirs;
	t_list	*lexar;
	t_list	**sections;
	t_list	*pipe;
}			t_parser;

#endif