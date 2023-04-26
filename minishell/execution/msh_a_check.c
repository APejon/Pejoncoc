/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_a_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:38:18 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/26 15:35:47 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief uses dup2 to provide different fds for stdout and stdin should they
 * be different
 * 
 * @param command struct containing fd_in and fd_out
 */
void	msh_update_fds(t_command *command)
{
	if (command->fd_out != STDOUT_FILENO)
		dup2(command->fd_out, STDOUT_FILENO);
	if (command->fd_in != STDIN_FILENO)
		dup2(command->fd_in, STDIN_FILENO);
	msh_protected_close(command->fd_out, -1, -2);
	msh_protected_close(command->fd_in, -1, -2);
}

/**
 * @brief Checks whether the command is builtin or binary, which will then be
 * executed as a child considering it is piped as well
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command Struct containing the command's details
 */
void	msh_check_command_piped(t_shell *shell, t_command *cmd, int t_fd, int i)
{
	char	**cmd_paths;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->cmd_args)
		{
			msh_update_fds(cmd);
			msh_protected_close(cmd->p_fd[0], -1, -2);
			msh_protected_close(t_fd, -1, -2);
			msh_protected_close(cmd->p_fd[1], -1, -2);
			if (msh_is_child(cmd) || msh_is_parent(cmd))
				msh_allocate_child_piped(shell, cmd, i);
			else
			{
				cmd_paths = msh_locate(shell, cmd);
				if (cmd_paths == NULL)
					msh_free_to_exit(shell);
				msh_execute(shell, cmd, cmd_paths);
			}
		}
		else
			msh_free_to_exit(shell);
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

	if (command->cmd_args)
	{
		if (msh_is_parent(command))
			msh_allocate_parent(shell, command);
		else
		{
			command->pid = fork();
			if (command->pid == 0)
			{
				msh_update_fds(command);
				if (msh_is_child(command))
					msh_allocate_child(shell, command);
				else
				{
					cmd_paths = msh_locate(shell, command);
					if (cmd_paths == NULL)
						msh_free_to_exit(shell);
					msh_execute(shell, command, cmd_paths);
				}
			}
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
void	msh_check_link(t_shell *shell)
{
	int		i;
	int		tmp_fd;

	g_stdin = 2;
	if (!(shell->command[1]))
	{
		if (msh_redirect(shell, shell->command[0], shell->command[0]->redir))
			msh_check_command(shell, shell->command[0]);
	}
	else
	{
		tmp_fd = dup(STDIN_FILENO);
		i = -1;
		while (shell->command[++i])
		{
			if (shell->command[i + 1])
				msh_pipe_command(shell, shell->command[i], &tmp_fd, i);
			else if (!shell->command[i + 1])
				msh_last_command(shell, shell->command[i], tmp_fd, i);
		}
	}
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
	int		status;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		msh_free(&shell->oldpwd);
		shell->oldpwd = getcwd(NULL, 0);
		msh_free(&cwd);
	}
	if (shell->nohd != 0)
		msh_create_here_doc(shell, shell->nohd);
	if (g_stdin == 3)
		msh_close_g_stdin();
	if (g_stdin == 0)
	{
		msh_check_link(shell);
		i = -1;
		while (shell->command[++i] && shell->command[i]->pid != 0)
			waitpid(shell->command[i]->pid, &status, 0);
		if (shell->command[0]->pid != 0)
			shell->exit_code = WEXITSTATUS(status);
	}
}
