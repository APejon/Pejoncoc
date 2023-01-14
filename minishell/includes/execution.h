/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:53:41 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/14 18:28:09 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*-------- msh_a_check.c --------*/
void	msh_check_command(t_shell *shell, t_command *command);
void	msh_check_link(t_shell *shell, t_command *command);

/*-------- msh_execute.c --------*/
void	msh_execute(t_shell *shell, char **cmd_paths);

/*-------- msh_locate.c --------*/
char	*msh_find_path(const t_env *enviro);
char	**msh_locate(t_shell *shell);

/*-------- msh_pipex_split.c --------*/
int		pipex_getwordcount(const char *s, char c);
void	pipex_assigns(const char *s, char **str, char c, int count);
char	**pipex_split(const char *s, char c);

#endif