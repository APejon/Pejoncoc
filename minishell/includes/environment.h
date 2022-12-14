/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:49:50 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/14 18:54:01 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

/*-------- msh_pwd.c --------*/
void	msh_update_oldpwd(t_shell *shell, char *oldpwd);
void	msh_update_pwd(t_shell *shell, char *pwd);

#endif