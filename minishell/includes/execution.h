/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:53:41 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/09 16:26:13 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*-------- msh_a_check.c --------*/
void	msh_update_fds(t_command *command);
void	msh_check_command_piped(t_shell *shell, t_command *command, int tmp_fd);
void	msh_check_command(t_shell *shell, t_command *command);
void	msh_check_link(t_shell *shell);
void	msh_command_dispenser(t_shell *shell);

/*-------- msh_execute.c --------*/
char	**msh_convert(t_env *enviro);
void	msh_execute(t_shell *shell, t_command *command, char **cmd_paths);

/*-------- msh_here_doc.c --------*/
void	msh_input_hd(t_direct *redir);
void	msh_create_here_doc(t_shell *shell, int nohd);

/*-------- msh_locate.c --------*/
char	*msh_find_path(t_env *enviro);
char	**msh_locate(t_shell *shell, t_command *command);

/*-------- msh_pipes.c --------*/
void	msh_create_pipe(t_shell *shell, t_command *command, int tmp_fd);
void	msh_pipe_command(t_shell *shell, t_command *command, int *tmp_fd);
void	msh_last_command(t_shell *shell, t_command *command, int tmp_fd);

/*-------- msh_pipex_split.c --------*/
int		pipex_getwordcount(const char *s, char c);
void	pipex_assigns(const char *s, char **str, char c, int count);
char	**pipex_split(const char *s, char c);

/*-------- msh_redirect.c --------*/
int		msh_in_direct(t_shell *shell, t_direct *redir, int fd);
int		msh_out_direct(t_shell *shell, t_direct *redir, int fd);
void	msh_redirect(t_shell *shell, t_command *command, t_direct **redir);

#endif