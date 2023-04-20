/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_a_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:38:18 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/20 13:49:29 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief uses dup2 to provide different fds for stdout and stdin should they
 * be different
 * 
 * @param command struct containing fd_in and fd_out
 */
void	msh_update_fds(t_shell *shell, t_command *command)
{
	msh_check_dir(shell, command, command->cmd_args[0]);
	if (command->fd_out != STDOUT_FILENO)
		dup2(command->fd_out, STDOUT_FILENO);
	if (command->fd_in != STDIN_FILENO)
		dup2(command->fd_in, STDIN_FILENO);
	if (command->fd_out != STDOUT_FILENO)
		close(command->fd_out);
	if (command->fd_in != STDIN_FILENO)
		close(command->fd_in);
}

/**
 * @brief Checks whether the command is builtin or binary, which will then be
 * executed as a child considering it is piped as well
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command Struct containing the command's details
 */
void	msh_check_command_piped(t_shell *shell, t_command *command, int tmp_fd)
{
	char	**cmd_paths;

	if (command->cmd_args)
	{
		command->pid = fork();
		if (command->pid == 0)
		{
			msh_update_fds(shell, command);
			if (command->p_fd[0] != STDIN_FILENO)
				close(command->p_fd[0]);
			close(tmp_fd);
			if (command->p_fd[1] != STDOUT_FILENO)
				close(command->p_fd[1]);
			if (msh_is_child(command) || msh_is_parent(command))
				msh_allocate_child_piped(shell, command);
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
				msh_update_fds(shell, command);
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
	int		check_failed;
	int		tmp_fd;

	check_failed = msh_check_redir(shell);
	if (check_failed)
		return ;
	if (!(shell->command[1]))
		msh_check_command(shell, shell->command[0]);
	else
	{
		tmp_fd = dup(STDIN_FILENO);
		i = -1;
		while (shell->command[++i])
		{
			if (shell->command[i + 1])
				msh_pipe_command(shell, shell->command[i], &tmp_fd);
			else if (!shell->command[i + 1])
				msh_last_command(shell, shell->command[i], tmp_fd);
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
	if (g_stdin != -3)
	{
		msh_check_link(shell);
		g_stdin = -2;
		i = -1;
		while (shell->command[++i] && shell->command[i]->pid != 0)
			waitpid(shell->command[i]->pid, &status, 0);
		if (shell->command[0]->pid != 0)
			shell->exit_code = WEXITSTATUS(status);
	}
}
