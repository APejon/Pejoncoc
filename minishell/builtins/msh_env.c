/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:44:19 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/16 20:16:17 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out one line of the env with a newline
 * 
 * @param env The struct containing the environment variable
 */
void	msh_print_env(t_env *env)
{
	pt_printf("%s%s\n", env->variable, env->value);
}

/**
 * @brief Uses the env command to list the environmental variables
 * 
 * @param env The struct containing the environment variables
 */
void	msh_env(t_env *env)
{
	t_env	*start;

	start = env;
	while (env)
	{
		if (env->next == NULL)
			break ;
		msh_print_env(env);
		env = env->next;
	}
	env = start;
}
