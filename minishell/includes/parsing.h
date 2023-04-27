/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:54:10 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/27 12:17:30 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//modules

typedef struct s_shell	t_shell;
typedef struct s_env	t_env;
typedef struct s_list	t_list;

/* Constructor */
void		free_sections(t_list *section);
void		null_making(t_list *lexar);
void		free_array(char **arr);
int			parser(t_shell *data, char **line);

/* Env Handler 1 and 2 */
int			remove_from_line(char *input, int i);
int			assign_meta(char **input, char *quote, int i);
char		*env_replace_hd(t_shell *shell, char *limiter);
char		*replace_str_env(t_shell *data, char *input, int idx, int flag);
int			env_resolver(t_shell *data, char **input, int i);
char		*str_replace_str_at(char *str, int idx, int length,
				char *replacement);
char		*get_env_value(t_env **env, char *variable);

/* Final Command Builder */
void		edge_case(t_list *search);
void		commands_init(t_shell *data, int p_count);
int			is_str_redir(char *str);
int			count_pipes_in_lexar(t_list *lexar);
int			split_into_commands(t_shell *data, t_list *lexar);

/* Parser 1 and 2 */
int			clean_quote(char **str);
int			lexer(char *line, t_list **lexar_list);
char		*str_remove_char_at1(char *str, int idx);
int			ft_isspace(int c);
int			is_meta_char(int c);

/* tansferstructs.c */

t_direct	*redir_content_init(t_shell *data, t_direct *redir,
				t_list **search);
t_direct	**redirs_transfer(t_shell *data, t_list *section, int no_of_redirs);
char		**cmd_args_transfer(t_list *section, int no_of_cmd_args);
void		count_inputs(t_shell *data, t_list *section);
void		transfer_structs(t_shell *data, t_list *section, int i,
				int p_count);

/* ambigious.c */
int			find_dollar(char *input, int i);
int			find_char(char *str, char c);
int			ambigious_redir(char *str, int idx, int length, char *replacement);

#endif
