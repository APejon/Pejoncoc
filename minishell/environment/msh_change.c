/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:38:41 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/16 22:04:56 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Updates the SHLVL within the environment variables, incrementing it
 * by one each time by converting it to an integer then back into a string
 * 
 * @param env The environment variable linked list containing the SHLVL variable
 */
void	msh_update_shlvl(t_env *env)
{
	int		previous_lvl;
	char	*updated_lvl;

	previous_lvl = ft_atoi(msh_find_env(env, "SHLVL="));
	updated_lvl = ft_itoa(previous_lvl + 1);
	msh_update_env(env, "SHLVL=", updated_lvl);
	msh_free(&updated_lvl);
}

/**
 * @brief Deletes an entire node from the environment
 * 
 * @param env The struct containing the environment variables
 */
void	msh_remove_node(t_env **env, t_env *target)
{
	t_env	*point;
	t_env	*anchor;

	point = (*env);
	if ((*env) == target)
	{
		(*env) = (*env)->next;
		ft_bzero(point->variable, ft_strlen(point->variable));
		if (point->value)
			ft_bzero(point->value, ft_strlen(point->value));
		msh_free_node(point);
		return ;
	}
	while (point->next != target && point->next)
		point = point->next;
	if (point->next == target)
	{
		anchor = point;
		point = point->next;
		anchor->next = anchor->next->next;
		ft_bzero(point->variable, ft_strlen(point->variable));
		if (point->value)
			ft_bzero(point->value, ft_strlen(point->value));
		msh_free_node(point);
	}
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
	pointer->variable = ft_strdup(variable);
	if (value)
		pointer->value = ft_strdup(value);
	else
		pointer->value = NULL;
	pointer->next = NULL;
	env->next = pointer;
}

void	msh_update_dec_env(t_env *env, char *variable, char *value)
{
	t_env	*start;

	start = env;
	value = ft_strjoin("\"", value);
	value = ft_free_strjoin(value, "\"", '1');
	while (env)
	{
		if (!ft_strncmp(env->variable, variable, ft_strlen(variable)))
		{
			ft_bzero(env->value, ft_strlen(env->value));
			msh_free(&(env->value));
			env->value = ft_free_strjoin(value, "\0", 1);
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
	msh_free(&value);
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
	t_env	*start;

	start = env;
	while (env)
	{
		if (!ft_strncmp(env->variable, variable, ft_strlen(variable)))
		{
			if (env->value)
			{
				ft_bzero(env->value, ft_strlen(env->value));
				msh_free(&(env->value));
			}
			env->value = ft_strdup(value);
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
