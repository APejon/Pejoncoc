/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_a_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:38:18 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/20 20:39:09 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_check_command_piped(t_shell *shell, t_command *command)
{
	char	**cmd_paths;
	int		status;
	pid_t	pid;

	if (command->cmd_args[0])
	{
		pid = fork();
		if ((msh_is_child(command) || msh_is_parent(command)) && pid == 0)
			msh_allocate_child(shell, command);
		else if (pid == 0)
		{
			cmd_paths = msh_locate(shell, command);
			if (cmd_paths == NULL)
				return ;
			msh_execute(shell, command, cmd_paths);
		}
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	}
}

/**
 * @brief Checks whether a command is builtin or executable, parent or child
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command Struct containing the command's details
 * @param flag Checks whether its a command for parent or child
 */
void	msh_check_command(t_shell *shell, t_command *command)
{
	char	**cmd_paths;
	int		status;
	pid_t	pid;

	if (command->cmd_args[0])
	{
		if (msh_is_parent(command))
			msh_allocate_parent(shell, command);
		else
		{
			pid = fork();
			if (msh_is_child(command) && pid == 0)
				msh_allocate_child(shell, command);
			else if (pid == 0)
			{
				cmd_paths = msh_locate(shell, command);
				if (cmd_paths == NULL)
					return ;
				msh_execute(shell, command, cmd_paths);
			}
			waitpid(pid, &status, 0);
			shell->exit_code = WEXITSTATUS(status);
		}
	}
}

void	msh_redirect(t_shell *shell, t_command *command)
{
	
}

/**
 * @brief Checks on the redirection, whether or not they are there
 * and which one they are.
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command block's components
 */
void	msh_check_link(t_shell *shell, t_command *command)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		shell->oldpwd = getcwd(NULL, 0);
	if (command->redir)
		msh_redirect(shell, command);
	else if (!shell->command[1])
		msh_check_command(shell, command);
	else
		msh_check_command_piped(shell, command);
	if (cwd)
		msh_free(&cwd);
}

//make central function here
