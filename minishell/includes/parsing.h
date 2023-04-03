/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhaidar <yhaidar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:54:10 by amalbrei          #+#    #+#             */
/*   Updated: 2023/03/24 12:27:23 by yhaidar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//modules

typedef struct s_shell	t_shell;
typedef struct s_env	t_env;
typedef struct s_list	t_list;

/* Constructor */
int		parser(t_shell *data, char **line);
void	null_making(t_list *lexar);
void	free_array(char **arr);

/* Env Handler 1 and 2 */
int		env_resolver(t_shell *data, char **input);
char	*str_replace_str_at(char *str, int idx, int length, char *replacement);
char	*get_env_value(t_env **to_env_list, char *env);

/* Final Command Builder */
int		count_pipes_in_lexar(t_list *lexar);
int		split_into_commands(t_shell *data, t_list *lexar);
int		char_array_len(char **arr);
int		is_str_redir(char *str);

/* Parser 1 and 2 */
int		lexer(char *line, t_list **lexar_list);
char	*str_remove_char_at1(char *str, int idx);
int		ft_isspace(int c);
int		is_meta_char(int c);

#endif
