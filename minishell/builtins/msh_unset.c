/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:12 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/12 16:00:46 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_pluck(t_shell *shell, t_command *command, int i)
{
	t_env	*check;
	t_env	*dec_check;

	check = msh_find_node(shell->env, command->cmd_args[i]);
	dec_check = msh_find_node(shell->dec_env, command->cmd_args[i]);
	if (check)
		msh_remove_node(shell->env,
			msh_find_node(shell->env, command->cmd_args[i]));
	if (dec_check)
		msh_remove_node(shell->dec_env,
			msh_find_node(shell->dec_env, command->cmd_args[i]));
}

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

	if (command->cmd_args[1])
	{
		i = 0;
		while (command->cmd_args[++i])
		{
			if (command->cmd_args[i][0] == '=')
			{
				write(2, "minishell: ", 11);
				write(2, command->cmd_args[0], ft_strlen(command->cmd_args[0]));
				write(2, ": ", 2);
				write(2, command->cmd_args[i], ft_strlen(command->cmd_args[i]));
				write(2, ": ", 2);
				write(2, "not a valid identifier\n", 23);
				shell->exit_code = 1;
				continue ;
			}
			else
				msh_pluck(shell, command, i);
		}
	}
	if (shell->exit_code != 1)
		shell->exit_code = 0;
}
