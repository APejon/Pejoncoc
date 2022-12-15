/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_change_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:38:41 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/15 18:31:44 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Changes the value of the environmental variable
 * 
 * @param env The struct containing the variables and values
 * @param value the value to be inputted into the node
 */
void	msh_add_value(t_env *env, char *value)
{
	env->value = malloc(sizeof(char) * ft_strlen(value) + 1);
	env->value = ft_strjoin(value, "\0");
}

/**
 * @brief Deletes the value from the environmental variable
 * 
 * @param env The struct containing the variables and values
 */
void	msh_remove_value(t_env *env)
{
	ft_bzero(env->value, ft_strlen(env->value));
	msh_free(&(env->value));
}

/**
 * @brief Creates a new node right after the last node of the env struct
 * 
 * @param env The struct containing the variables and values
 * @param variable Contents BEFORE the '=', ex: "PWD="
 * @param value Contents AFTER the '=', ex: "/Users/amalbrei"
 */
void	msh_create_node(t_env *env, char *variable, char *value)
{
	t_env	*pointer;

	pointer = malloc(sizeof(t_env));
	pointer->variable = variable;
	pointer->value = value;
	pointer->next = NULL;
	env->next = pointer;
}

/**
 * @brief Updates the environment variable linked list with new values
 * 
 * @param env The struct containing the variables and values
 * @param variable Contents BEFORE the '=', ex: "PWD="
 * @param value Contents AFTER the '=', ex: "/Users/amalbrei"
 */
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
