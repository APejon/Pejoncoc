/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:12 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/19 17:16:09 by amalbrei         ###   ########.fr       */
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
	if (ft_strchr(command->target, '='))
	{
		msh_error_print(shell, command, "not a valid identifier");
		return ;
	}
	else
	{
		msh_remove_node(msh_find_node(shell->env, command->target));
		msh_remove_node(msh_find_node(shell->dec_env, command->target));
		//code msh_remove_node
	}
}
