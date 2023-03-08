/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_a_allocate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:28:47 by amalbrei          #+#    #+#             */
/*   Updated: 2023/03/07 14:18:01 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Checks whether the command is a builtin or not for a parent process
 * 
 * @param shell The struct containing variables of used within the shell
 * @return true The command is a builtin
 * @return false The command is something else
 */
bool	msh_is_parent(t_command *command)
{
	if (!ft_strncmp(command->cmd_args[0], "cd", 3)
		|| !ft_strncmp(command->cmd_args[0], "exit", 5)
		|| !ft_strncmp(command->cmd_args[0], "export", 7)
		|| !ft_strncmp(command->cmd_args[0], "unset", 6))
		return (true);
	else
		return (false);
}

bool	msh_is_child(t_command *command)
{
	if (!ft_strncmp(command->cmd_args[0], "echo", 5)
		|| !ft_strncmp(command->cmd_args[0], "pwd", 4)
		|| !ft_strncmp(command->cmd_args[0], "env", 4))
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
void	msh_allocate_child(t_shell *shell, t_command *command)
{
	if (!ft_strncmp(command->cmd_args[0], "cd", 3))
		msh_cd(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "echo", 5))
		msh_echo(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "env", 4))
		msh_env(shell, shell->env);
	else if (!ft_strncmp(command->cmd_args[0], "exit", 5))
		msh_exit(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "export", 7))
		msh_export(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "pwd", 4))
		msh_pwd(shell);
	else if (!ft_strncmp(command->cmd_args[0], "export", 7))
		msh_export(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "unset", 6))
		msh_unset(shell, command);
	msh_free_to_exit(shell);
}

/**
 * @brief Finds out which command is being called from a parent process
 * perspective
 * 
 * @param shell The struct containing variables of used within the shell
 */
void	msh_allocate_parent(t_shell *shell, t_command *command)
{
	if (!ft_strncmp(command->cmd_args[0], "cd", 3))
		msh_cd(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "exit", 5))
		msh_exit(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "export", 7))
		msh_export(shell, command);
	else if (!ft_strncmp(command->cmd_args[0], "unset", 6))
		msh_unset(shell, command);
}
