/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:53:07 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/16 13:53:27 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*-------- allocate --------*/
bool	msh_is_parent(t_command *command);
bool	msh_is_child(t_command *command);
void	msh_allocate_child_piped(t_shell *shell, t_command *command);
void	msh_allocate_child(t_shell *shell, t_command *command);
void	msh_allocate_parent(t_shell *shell, t_command *command);

/*-------- cd -------- */
void	msh_cd_target(t_shell *shell, t_command *command);
void	msh_cd_parent(t_shell *shell, t_command *command);
void	msh_cd_home(t_shell *shell, t_command *command);
void	msh_cd(t_shell *shell, t_command *command);

/*-------- echo --------*/
void	msh_echo(t_shell *shell, t_command *command);

/*-------- env --------*/
void	msh_print_env(t_env *env);
void	msh_env(t_shell *shell, t_env *env);

/*-------- exit --------*/
void	msh_exit(t_shell *shell, t_command *command);

/*-------- export --------*/
void	msh_export_node(t_shell *shell, char *target, char *value);
char	*msh_separate(char *target, char sep);
void	msh_prep_export(t_shell *shell, t_command *command, char *target);
void	msh_list_dec(t_env *dec_env);
void	msh_export(t_shell *shell, t_command *command);

/*-------- pwd --------*/
void	msh_print_pwd(char *pwd);
void	msh_pwd(t_shell *shell);

/*-------- unset --------*/
int		msh_invalid(char *identi, char flag);
void	msh_pluck(t_shell *shell, t_command *command, int i);
void	msh_unset(t_shell *shell, t_command *command);

#endif