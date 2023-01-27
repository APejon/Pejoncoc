/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_a_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:38:18 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/27 21:04:29 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether the command is builtin or binary, which will then be
 * executed as a child considering it is piped as well
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command Struct containing the command's details
 */
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

/**
 * @brief Checks on the redirection, whether or not they are there
 * and which one they are.
 * 
 * @param shell The struct containing variables used within the shell
 * @param command The struct containing the command block's components
 * @param fd File descriptors to be changed if redirections exist
 */
void	msh_check_link(t_shell *shell, t_command *command)
{
	if (command->redir)
		msh_redirect(shell, command, command->redir);
	else if (!shell->command[1])
		msh_check_command(shell, command);
	else
		msh_check_command_piped(shell, command);
}

/**
 * @brief Prepares the fds, current working directory and here_doc files (if 
 * applicable) before moving on to the command blocks
 * 
 * @param shell The struct containing variables used within the shell
 */
void	msh_command_dispenser(t_shell *shell)
{
	int		i;
	char	*cwd;

	i = -1;
	cwd = getcwd(NULL, 0);
	if (cwd)
		shell->oldpwd = getcwd(NULL, 0);
	if (shell->nohd != 0)
		msh_create_here_doc(shell, shell->nohd);
	while (shell->command[++i])
	{
		shell->command[i]->fd_in = 0;
		shell->command[i]->fd_out = 1;
		msh_check_link(shell, shell->command[i]); //code pipes here somewhere
	}
	if (cwd)
		msh_free(&cwd);
}
