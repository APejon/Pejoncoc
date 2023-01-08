/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:44:19 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/08 18:53:40 by amalbrei         ###   ########.fr       */
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
void	msh_env(t_shell *shell, t_env *env)
{
	t_env	*start;

	start = env;
	while (env)
	{
		msh_print_env(env);
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	env = start;
	shell->exit_code = 0;
	shell->yet_to_execute = 0;
}
