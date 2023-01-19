/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:12 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/19 19:36:52 by amalbrei         ###   ########.fr       */
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
	int		i;
	t_env	*check;
	t_env	*dec_check;

	if (command->cmd_args[1])
	{
		i = 0;
		while (command->cmd_args[++i])
		{
			if (command->cmd_args[i][0] == '=')
				msh_print_error(shell, command, "not a valid identifier", 1);
			else
			{
				check = msh_find_node(shell->env, command->cmd_args[i]);
				dec_check = msh_find_node(shell->dec_env, command->cmd_args[i]);
				if (check)
					msh_remove_node(shell->env,
						msh_find_node(shell->env, command->cmd_args[i]));
				if (dec_check)
					msh_remove_node(shell->dec_env,
						msh_find_node(shell->dec_env, command->cmd_args[i]));
			}
		}
	}
	shell->exit_code = 0;
}
