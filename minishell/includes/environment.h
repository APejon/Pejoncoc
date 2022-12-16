/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:49:50 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/16 19:04:45 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

/*-------- msh_change_env.c --------*/
void	msh_add_value(t_env *env, char *value);
void	msh_remove_value(t_env *env);
void	msh_create_node(t_env *env, char *variable, char *value);
void	msh_update_env(t_env *env, char *variable, char *value);

/*-------- msh_find.c --------*/
t_env	*msh_find_last_node(t_env env);
char	*msh_find_env(t_env *env, char *line);

#endif