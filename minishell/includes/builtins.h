/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:53:07 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/16 20:19:12 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*-------- cd -------- */
void	msh_cd_target(t_shell *shell, char *target);
void	msh_cd_parent(t_shell *shell, char *parent);
void	msh_cd_home(t_shell *shell, char *home);
void	msh_cd(t_shell *shell, t_command *command);

/*-------- echo --------*/
void	msh_echo(t_shell *shell, t_command *command);

/*-------- env --------*/
void	msh_print_env(t_env *env);
void	msh_env(t_env *env);

/*-------- exit --------*/
void	msh_exit(t_command *command);

/*-------- export --------*/
char	*msh_quotes(char *value);
char	*msh_separate(char *target);
void	msh_print_dec(t_env *env);
void	msh_list_dec(t_env *dec_env);
void	msh_export(t_shell *shell, t_command *command);

#endif