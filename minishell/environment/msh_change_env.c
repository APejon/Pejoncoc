/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_change_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:38:41 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/15 16:21:29 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_add_value(t_env *env, char *value)
{
	env->value = malloc(sizeof(char) * ft_strlen(value) + 1);
	env->value = ft_strjoin(value, "\0");
}

void	msh_remove_value(t_env *env)
{
	ft_bzero(env->value, ft_strlen(env->value));
	msh_free(&(env->value));
}

void	msh_create_node(t_env *env, char *variable, char *value)
{
	t_env	*pointer;

	pointer = malloc(sizeof(t_env));
	pointer->variable = variable;
	pointer->value = value;
	pointer->next = NULL;
	env->next = pointer;
}

void	msh_update_env(t_env *env, char *variable, char *value)
{
	bool	changed;
	t_env	*last;
	t_env	*start;

	changed = false;
	start = env;
	while (env)
	{
		if (!ft_strncmp(env->variable, variable, ft_strlen(variable)))
		{
			msh_remove_value(env);
			msh_add_value(env, value);
			break ;
		}
		else if (env->next == NULL)
		{
			msh_create_node(env, variable, value);
			break ;
		}
		env = env->next;
	}
	env = start;
}
