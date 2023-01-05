/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_allocate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:01:30 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/04 15:58:30 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds out which command is being called
 * 
 * @param shell The struct containing variables of used within the shell
 */
void	msh_allocate(t_shell *shell)
{
	if (!ft_strncmp(shell->command->command, "cd", 3))
		msh_cd(shell, shell->command);
	if (!ft_strncmp(shell->command->command, "echo", 5))
		msh_echo(shell, shell->command);
	if (!ft_strncmp(shell->command->command, "env", 4))
		msh_env(shell, shell->env);
	if (!ft_strncmp(shell->command->command, "exit", 5))
		msh_exit(shell, shell->command);
	if (!ft_strncmp(shell->command->command, "export", 7))
		msh_export(shell, shell->command);
	if (!ft_strncmp(shell->command->command, "pwd", 4))
		msh_pwd(shell, shell->command);
	if (!ft_strncmp(shell->command->command, "unset", 6))
		msh_unset(shell, shell->command);
}
