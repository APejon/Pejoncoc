/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:53:07 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/15 17:02:17 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*-------- cd -------- */
void	msh_cd_target(t_shell *shell, char *target);
void	msh_cd_parent(t_shell *shell, char *parent);
void	msh_cd_home(t_shell *shell, char *home);
void	msh_cd(t_shell *shell);

/*-------- echo --------*/
void	msh_echo(t_shell *shell);

#endif