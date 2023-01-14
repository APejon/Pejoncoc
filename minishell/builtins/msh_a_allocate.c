/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_a_allocate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:28:47 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/14 19:05:40 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether the command is a builtin or not for a parent process
 * 
 * @param shell The struct containing variables of used within the shell
 * @return true The command is a builtin
 * @return false The command is something else
 */
bool	msh_is_parent(t_shell *shell)
{
	if (!ft_strncmp(shell->command->command, "cd", 3)
		|| !ft_strncmp(shell->command->command, "exit", 5)
		|| !ft_strncmp(shell->command->command, "export", 7)
		|| !ft_strncmp(shell->command->command, "unset", 6))
		return (true);
	else
		return (false);
}

bool	msh_is_child(t_shell *shell)
{
	if (!ft_strncmp(shell->command->command, "echo", 5)
		|| !ft_strncmp(shell->command->command, "pwd", 4)
		|| !ft_strncmp(shell->command->command, "env", 4))
		return (true);
	else
		return (false);
}

/**
 * @brief Finds out which command is being called from a child process 
 * perspective
 * 
 * @param shell The struct containing variables of used within the shell
 */
void	msh_allocate_child(t_shell *shell)
{
	if (!ft_strncmp(shell->command->command, "cd", 3))
		msh_cd(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "echo", 5))
		msh_echo(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "env", 4))
		msh_env(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "exit", 5))
		msh_exit(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "export", 7))
		msh_export(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "pwd", 4))
		msh_pwd(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "export", 7))
		msh_export(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "unset", 6))
		msh_unset(shell, shell->command);
	exit (shell->exit_code);
}

/**
 * @brief Finds out which command is being called from a parent process
 * perspective
 * 
 * @param shell The struct containing variables of used within the shell
 */
void	msh_allocate_parent(t_shell *shell)
{
	if (!ft_strncmp(shell->command->command, "cd", 3))
		msh_cd(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "exit", 5))
		msh_exit(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "export", 7))
		msh_export(shell, shell->command);
	else if (!ft_strncmp(shell->command->command, "unset", 6))
		msh_unset(shell, shell->command);
}
