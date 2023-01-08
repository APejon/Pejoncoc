/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:12 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/08 18:55:56 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Uses the unset command to remove the variables from the environment
 * and the export list
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 */
void	msh_unset(t_shell *shell, t_command *command)
{
	if (command->target)
	{
		if (ft_strchr(command->target, '='))
		{
			msh_print_error(shell, command, "not a valid identifier");
			shell->exit_code = 1;
			shell->yet_to_execute = 0;
			return ;
		}
		else
		{
			msh_remove_node(shell->env, msh_find_node(shell->env,
					command->target));
			msh_remove_node(shell->dec_env, msh_find_node(shell->dec_env,
					command->target));
		}
	}
	shell->exit_code = 0;
	shell->yet_to_execute = 0;
}
